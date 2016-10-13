"""
Author: Leo Vidarte <http://nerdlabs.com.ar>

This is free software,
you can redistribute it and/or modify it
under the terms of the GPL version 3
as published by the Free Software Foundation.

"""

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
