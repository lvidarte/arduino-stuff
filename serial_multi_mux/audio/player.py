"""
Author: Leo Vidarte <http://nerdlabs.com.ar>

This is free software,
you can redistribute it and/or modify it
under the terms of the GPL version 3
as published by the Free Software Foundation.

"""

import pyaudio
import wave
import sys
import struct

CHUNK = 1024

if len(sys.argv) < 2:
    print("Plays a wave file.\n\nUsage: %s filename.wav" % sys.argv[0])
    sys.exit(-1)

w = wave.open(sys.argv[1], 'rb')
(nchannels, sampwidth, framerate, nframes, comptype, compname) = w.getparams()

p = pyaudio.PyAudio()

stream = p.open(format=p.get_format_from_width(sampwidth),
                channels=nchannels,
                rate=framerate,
                output=True)

def data_analyzer(data):
    if len(data) == CHUNK * 4:
        size = CHUNK * 2
        values = struct.unpack("%dh" % size, data)
        print "---"
        for i in range(0, CHUNK, 512):
            print values[i]

while True:
    data = w.readframes(CHUNK)
    if not data:
        break
    data_analyzer(data)
    #stream.write(data)

#stream.stop_stream()
stream.close()
p.terminate()
