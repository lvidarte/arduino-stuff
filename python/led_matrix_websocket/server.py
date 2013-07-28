from tornado import options, ioloop, web, websocket

USB_PORT = '/dev/ttyACM0'
ADDR = '192.168.2.99'
PORT = 8888


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
    'EI': 'http://www.pagina12.com.ar/diario/rss/principal.xml',
    'UN': 'http://www.pagina12.com.ar/diario/rss/ultimas_noticias.xml'
}


def publisher():
    logging.info('Starting publisher')
    while True:
        if Glob.arduino_ready:
            with Glob.lock:
                if Glob.queue:
                    Glob.last_sent_message = Glob.queue.pop(0)
                    conn.write(Glob.last_sent_message[2] + '\0')
                    logging.info('Message from %s sent to Arduino: %s',
                                 Glob.last_sent_message[1],
                                 Glob.last_sent_message[2])
                else:
                    Glob.last_sent_message = ('', '', '')
                    get_feeds()
                for client in Glob.clients:
                    client.write_message(MSG_SENT % Glob.last_sent_message)
        time.sleep(5)


def get_feeds():
    for name, url in FEEDS.items():
        d = feedparser.parse(url)
        for entry in d['entries']:
            message = parse_message("~%s" % entry['title'])
            msg = (Glob.count, 'SERVER', message)
            Glob.queue.append(msg)
            Glob.count += 1
            for client in Glob.clients:
                client.write_message(MSG_ADDED % msg)
            logging.info('Message received from %s: %s',
                         'SERVER', message)


def parse_message(message):
    """ * Only printable ascii chars (in range from 32 to 126)
        * Remove extra spaces
        * 64 chars length
    """
    _ = message.strip()
    _ = re.sub(' +', ' ', _)
    _ = unicodedata.normalize('NFKD', _).encode('ascii', 'ignore')
    _ = "".join([c for c in _ if ord(c) >= 32 and ord(c) <= 126])
    if len(_) > 64:
        _ = _[:64]
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
    last_sent_message = None
    lock = threading.Lock()
    count = 0
    publisher = threading.Thread(target=publisher)
    arduino_ready = False
    arduino_check_state = threading.Thread(target=check_state)


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
                msg = (Glob.count, self.request.remote_ip, message)
                Glob.queue.append(msg)
                Glob.count += 1
                for client in Glob.clients:
                    client.write_message(MSG_ADDED % msg)
                logging.info('Message received from %s: %s',
                             self.request.remote_ip, message)

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


