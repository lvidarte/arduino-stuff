from tornado import ioloop, web, websocket

#import serial
#conn = serial.Serial('/dev/ttyACM0', 9600)

import threading
import time


def publisher():
    print "Starting publisher"
    while True:
        with Glob.lock:
            if Glob.queue:
                Glob.message = Glob.queue.pop(0)
                print "Sending to Arduino:", Glob.message[1]
            else:
                Glob.message = ('', '')
            for client in Glob.clients:
                client.write_message('d%s\n%s' % Glob.message)
        time.sleep(20)


class Glob:
    queue = []
    clients = []
    message = ''
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
                    self.write_message('a%s\n%s' % message)
            self.write_message('d%s\n%s' % Glob.message)
        print "Websocket opened"

    def on_message(self, message):
        with Glob.lock:
            msg = (Glob.count, message)
            Glob.queue.append(msg)
            Glob.count += 1
            for client in Glob.clients:
                client.write_message('a%s\n%s' % msg)
            print "Received from client:", message

    def on_close(self):
        if Glob.clients:
            Glob.clients.remove(self)
        print "Websocket closed"


if __name__ == '__main__':
    application = web.Application([
        (r'/', PublisherHandler),
        (r'/publisher', PublisherWebSocketHandler),
        ], debug=True)
    application.listen(8888, address='0.0.0.0')
    Glob.publisher.start()
    ioloop.IOLoop.instance().start()


