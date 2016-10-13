"""
Author: Leo Vidarte <http://nerdlabs.com.ar>

This is free software,
you can redistribute it and/or modify it
under the terms of the GPL version 3
as published by the Free Software Foundation.

"""

import wave
import sys
import struct
from math import log10

CHUNK = 256
DBS = [-19, -13, -9, -7, -5, -3, -2, -1, 0]


def open_wave(filename):
    return wave.open(filename, 'rb')
    #(nchannels, sampwidth, framerate, nframes, comptype, compname) = w.getparams()

def data_analyzer(w, chunk=CHUNK):
    result = []
    while True:
        data = w.readframes(chunk)
        if not data:
            break
        values = struct.unpack("%dh" % (len(data) / 2), data)
        left = analyze_range(values[0::2])
        right = analyze_range(values[1::2])
        result.append((left, right))
    return result

def analyze_range(values):
    max = 0
    for v in values:
        if v > max:
            max = v

    if max:
        amplitude = max / 32767.0
        dB = 20 * log10(amplitude)
        for i, v in enumerate(DBS):
            if dB <= v:
                return i

    return 0


if __name__ == '__main__':

    if len(sys.argv) < 2:
        print("Plays a wave file.\n\nUsage: %s filename.wav" % sys.argv[0])
        sys.exit(-1)

    w = open_wave(sys.argv[1])
    print data_analyzer(w)
