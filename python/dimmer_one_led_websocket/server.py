from tornado import ioloop, web, websocket
import serial

conn = serial.Serial('/dev/ttyACM0', 9600)
websocket_clients = []


class DimmerHandler(web.RequestHandler):
    def get(self):
        self.render('dimmer.html')

class DimmerWebSocketHandler(websocket.WebSocketHandler):
    def open(self):
        websocket_clients.append(self)
        print "Websocket opened"

    def on_message(self, message):
        for client in websocket_clients:
            conn.write(chr(int(message)))
            client.write_message(message)
        print "Message:", message

    def on_close(self):
        if websocket_clients:
            websocket_clients.remove(self)
        print "Websocket closed"


if __name__ == '__main__':
    application = web.Application([
        (r'/', DimmerHandler),
        (r'/dimmer', DimmerWebSocketHandler),
        ], debug=True)
    application.listen(8888, address='0.0.0.0')
    ioloop.IOLoop.instance().start()

