from tornado import options, ioloop, web, websocket

USB_PORT = '/dev/ttyACM0'
ADDR = '192.168.2.100'
PORT = 8888
MSG_LEN = 512


import serial
conn = serial.Serial(USB_PORT, 9600)

import os.path
import re
import threading
import time
import unicodedata
import logging
import feedparser


ROOT_DIR = os.path.dirname(os.path.realpath(__file__))
MSG_SENT = 'SENT\n%s\n%s\n%s'
MSG_ADDED = 'ADDED\n%s\n%s\n%s'


FEEDS = {
    #'EI': 'http://www.pagina12.com.ar/diario/rss/principal.xml',
    'UN': 'http://www.pagina12.com.ar/diario/rss/ultimas_noticias.xml'
}


def publisher():
    logging.info('Starting publisher')
    while True:
        if Glob.arduino_ready:
            with Glob.lock:
                message = Glob.get_next_message()
                if message:
                    Glob.last_sent_message = message
                    conn.write(Glob.last_sent_message[2] + '\0')
                    logging.info('Message from %s sent to Arduino: %s',
                                 Glob.last_sent_message[1],
                                 Glob.last_sent_message[2])
                else:
                    Glob.last_sent_message = ('', '', '')
                for client in Glob.clients:
                    client.write_message(MSG_SENT % Glob.last_sent_message)
        time.sleep(5)


def parse_message(message):
    """ * Only printable ascii chars (in range from 32 to 126)
        * Remove extra spaces
        * MSG_LEN chars length
    """
    _ = message.strip()
    _ = re.sub(' +', ' ', _)
    _ = unicodedata.normalize('NFKD', _).encode('ascii', 'ignore')
    _ = "".join([c for c in _ if ord(c) >= 32 and ord(c) <= 126])
    if len(_) > MSG_LEN:
        _ = _[:MSG_LEN]
    _ = _ + ' '
    return _


def check_state():
    logging.info('Starting Arduino check status')
    while True:
        try:
            data = conn.read()
            Glob.arduino_ready = True if data == '1' else False
            logging.info("Arduino state %s", Glob.arduino_ready)
        except Exception as e:
            logging.exception(e)


class Glob:
    queue = []
    clients = []
    feeds = []
    last_sent_message = None
    lock = threading.Lock()
    count = 0
    publisher = threading.Thread(target=publisher)
    arduino_ready = False
    arduino_check_state = threading.Thread(target=check_state)

    @staticmethod
    def add_message(message, from_):
        message_ = (Glob.count, from_, message)
        Glob.queue.append(message_)
        Glob.count += 1
        Glob.send_to_clients(message_)

    @staticmethod
    def get_next_message():
        if Glob.queue:
            return Glob.queue.pop(0)
        if Glob.feeds:
            Glob.add_message(Glob.feeds.pop(0), from_='SERVER')
            return Glob.queue.pop(0)
        Glob.read_feeds()

    @staticmethod
    def read_feeds():
        for source, url in FEEDS.items():
            d = feedparser.parse(url)
            for entry in d['entries']:
                feed = parse_message("~%s: %s" % (source, entry['title']))
                Glob.feeds.append(feed)

    @staticmethod
    def send_to_clients(message):
        for client in Glob.clients:
            client.write_message(MSG_ADDED % message)
        logging.info('Message received from %s: %s', message[1], message[2])


class PublisherHandler(web.RequestHandler):

    def get(self):
        self.render('publisher.html')


class PublisherWebSocketHandler(websocket.WebSocketHandler):

    def open(self):
        with Glob.lock:
            Glob.clients.append(self)
            if Glob.queue:
                for message in Glob.queue:
                    self.write_message(MSG_ADDED % message)
            if Glob.last_sent_message:
                self.write_message(MSG_SENT % Glob.last_sent_message)
            logging.info('Websocket opened from %s', self.request.remote_ip)

    def on_message(self, message):
        message = parse_message(message)
        if message:
            with Glob.lock:
                from_ = self.request.remote_ip
                Glob.add_message(message, from_)

    def on_close(self):
        with Glob.lock:
            if Glob.clients:
                Glob.clients.remove(self)
                logging.info('Websocket closed from %s',
                             self.request.remote_ip)



if __name__ == '__main__':
    application = web.Application([
        (r'/favicon.ico', web.StaticFileHandler, {'path': 'favicon.ico'}),
        (r'/publisher', PublisherWebSocketHandler),
        (r'/', PublisherHandler),
        ], static_path=ROOT_DIR, debug=True, enable_pretty_logging=True)
    application.listen(PORT, address=ADDR)
    options.parse_command_line()
    logging.info('Starting server at %s:%s' % (ADDR, PORT))
    Glob.publisher.start()
    Glob.arduino_check_state.start()
    ioloop.IOLoop.instance().start()


