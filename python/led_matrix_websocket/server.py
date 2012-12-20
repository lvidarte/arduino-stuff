from tornado import ioloop, web, websocket

#import serial
#conn = serial.Serial('/dev/ttyACM0', 9600)

import os.path
import re
import threading
import time
import unicodedata


ROOT_DIR = os.path.dirname(os.path.realpath(__file__))
MSG_DURATION = 20 # sec
MSG_SENT = 'SENT\n%s\n%s\n%s'
MSG_ADDED = 'ADDED\n%s\n%s\n%s'


def publisher():
    print 'Starting publisher'
    while True:
        with Glob.lock:
            if Glob.queue:
                Glob.last_sent_message = Glob.queue.pop(0)
                print 'Message from %s sent to Arduino: %s' % (
                        Glob.last_sent_message[1], Glob.last_sent_message[2])
            else:
                Glob.last_sent_message = ('', '', '')
            for client in Glob.clients:
                client.write_message(MSG_SENT % Glob.last_sent_message)
        time.sleep(MSG_DURATION)


class Glob:
    queue = []
    clients = []
    last_sent_message = None
    lock = threading.Lock()
    count = 0
    publisher = threading.Thread(target=publisher)


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
            print 'Websocket opened from', self.request.remote_ip

    def on_message(self, message):
        message = self.parse_message(message)
        if message:
            with Glob.lock:
                msg = (Glob.count, self.request.remote_ip, message)
                Glob.queue.append(msg)
                Glob.count += 1
                for client in Glob.clients:
                    client.write_message(MSG_ADDED % msg)
                print 'Message received from %s: %s' % (self.request.remote_ip,
                                                        message)

    def on_close(self):
        with Glob.lock:
            if Glob.clients:
                Glob.clients.remove(self)
                print 'Websocket closed from', self.request.remote_ip

    def parse_message(self, message):
        """ * Only printable ascii chars (in range from 32 to 126)
            * Remove extra spaces
            * 64 chars length
        """
        _ = message.strip()
        _ = re.sub(' +', ' ', _)
        _ = unicodedata.normalize('NFKD', _).encode('ascii', 'ignore')
        _ = "".join([c for c in _ if ord(c) >= 32 and ord(c) <= 126])
        return _ if len(_) <= 64 else _[:64]


if __name__ == '__main__':
    application = web.Application([
        (r'/favicon.ico', web.StaticFileHandler, {'path': 'favicon.ico'}),
        (r'/publisher', PublisherWebSocketHandler),
        (r'/', PublisherHandler),
        ], static_path=ROOT_DIR, debug=True)
    application.listen(8888, address='0.0.0.0')
    Glob.publisher.start()
    ioloop.IOLoop.instance().start()


