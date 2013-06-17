import wave
import sys
import struct

CHUNK = 256


def open_wave(filename):
    return wave.open(filename, 'rb')
    #(nchannels, sampwidth, framerate, nframes, comptype, compname) = w.getparams()


def data_analyzer(w, chunk=CHUNK):
    result = []
    while True:
        data = w.readframes(CHUNK)
        if not data:
            break
        values = struct.unpack("%dh" % (len(data) / 2), data)
        left = analyze_range(values[0::2])
        right = analyze_range(values[1::2])
        result.append((left, right))
    return result

def analyze_range(values):
    out = {0: 0, 1: 0, 2: 0, 3: 0, 4: 0, 5: 0, 6: 0, 7: 0, 8: 0}
    for v in values:
        v = abs(v)
        if v < 3640:
            out[0] += 1
        elif v < 7280:
            out[1] += 1
        elif v < 10920:
            out[2] += 1
        elif v < 14560:
            out[3] += 1
        elif v < 18200:
            out[4] += 1
        elif v < 21840:
            out[5] += 1
        elif v < 25480:
            out[6] += 1
        elif v < 29120:
            out[7] += 1
        else:
            out[8] += 1
    print out
    return max(out.iterkeys(), key=lambda k: out[k])



if __name__ == '__main__':

    if len(sys.argv) < 2:
        print("Plays a wave file.\n\nUsage: %s filename.wav" % sys.argv[0])
        sys.exit(-1)

    w = open_wave(sys.argv[1])
    print data_analyzer(w)
