USB_PORT = '/dev/ttyACM0'
ADDR = '127.0.0.1'
PORT = 8888

FEEDS = {
    '/.': 'http://barrapunto.com/index.rss',
    }

try:
    from local_config import *
except:
    pass
