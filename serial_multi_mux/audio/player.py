import pyaudio
import wave
import sys
import struct

CHUNK = 1024

if len(sys.argv) < 2:
    print("Plays a wave file.\n\nUsage: %s filename.wav" % sys.argv[0])
    sys.exit(-1)

wf = wave.open(sys.argv[1], 'rb')
#(nchannels, sampwidth, framerate, nframes, comptype, compname) = wf.getparams()

p = pyaudio.PyAudio()

stream = p.open(format=p.get_format_from_width(wf.getsampwidth()),
                channels=wf.getnchannels(),
                rate=wf.getframerate(),
                output=True)

def data_analyzer(data):
    if len(data) == CHUNK * 4:
        size = CHUNK * 2
        values = struct.unpack("%dh" % size, data)
        print "---"
        for i in range(0, CHUNK, 512):
            print values[i]

while True:
    data = wf.readframes(CHUNK)
    if not data:
        break
    data_analyzer(data)
    stream.write(data)

stream.stop_stream()
stream.close()
p.terminate()
