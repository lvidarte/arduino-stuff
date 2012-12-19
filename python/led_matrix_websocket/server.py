from tornado import ioloop, web, websocket

#import serial
#conn = serial.Serial('/dev/ttyACM0', 9600)

import threading
import time
import unicodedata


MSG_DURATION = 60 # sec

MSG_SENT = 'SENT\n%s\n%s\n%s'
MSG_ADDED = 'ADDED\n%s\n%s\n%s'


def publisher():
    print "Starting publisher"
    while True:
        with Glob.lock:
            if Glob.queue:
                Glob.last_sent_message = Glob.queue.pop(0)
                print "Sending to Arduino:", Glob.last_sent_message[-1]
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
        Glob.clients.append(self)
        with Glob.lock:
            if Glob.queue:
                for message in Glob.queue:
                    self.write_message(MSG_ADDED % message)
            self.write_message(MSG_SENT % Glob.last_sent_message)
        print "Websocket opened"

    def on_message(self, message):
        with Glob.lock:
            message = self.parse_message(message)
            if message:
                msg = (Glob.count, self.request.remote_ip, message)
                Glob.queue.append(msg)
                Glob.count += 1
                for client in Glob.clients:
                    client.write_message(MSG_ADDED % msg)
                print "Received from client:", message

    def on_close(self):
        if Glob.clients:
            Glob.clients.remove(self)
        print "Websocket closed"

    def parse_message(self, message):
        _ = message.strip()
        _ = unicodedata.normalize('NFKD', _).encode('ascii', 'ignore')
        # only printable ascii chars (in range from 32 to 126)
        _ = "".join([c for c in _ if ord(c) >= 32 and ord(c) <= 126])
        return _


if __name__ == '__main__':
    application = web.Application([
        (r'/', PublisherHandler),
        (r'/publisher', PublisherWebSocketHandler),
        ], debug=True)
    application.listen(8888, address='0.0.0.0')
    Glob.publisher.start()
    ioloop.IOLoop.instance().start()


