from tornado import ioloop, web, websocket
import serial

conn = serial.Serial('/dev/ttyACM0', 9600)


class DimmerHandler(web.RequestHandler):
    def get(self):
        self.render('dimmer.html')

class DimmerWebSocketHandler(websocket.WebSocketHandler):

    # Static variables
    clients = []
    last_message = "0"

    def open(self):
        DimmerWebSocketHandler.clients.append(self)
        self.write_message(DimmerWebSocketHandler.last_message)
        print "Websocket opened", DimmerWebSocketHandler.last_message

    def on_message(self, message):
        DimmerWebSocketHandler.last_message = message
        conn.write(chr(int(message)))
        for client in DimmerWebSocketHandler.clients:
            if client != self:
                client.write_message(message)
        print "Message:", message

    def on_close(self):
        if DimmerWebSocketHandler.clients:
            DimmerWebSocketHandler.clients.remove(self)
        print "Websocket closed"


if __name__ == '__main__':
    application = web.Application([
        (r'/', DimmerHandler),
        (r'/dimmer', DimmerWebSocketHandler),
        ], debug=True)
    application.listen(8888, address='0.0.0.0')
    ioloop.IOLoop.instance().start()

