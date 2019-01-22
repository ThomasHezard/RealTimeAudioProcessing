import numpy as np
import scipy.io.wavfile as wavfile
import sys

inpcmfile = sys.argv[1]
samplerate = 44100#sys.argv[2]
outwavfile = sys.argv[2]

print("Converting mono {}Hz pcm float32 file {} to wav file {}...".format(samplerate, inpcmfile, outwavfile))

with open(inpcmfile, 'rb') as f:
    data = np.fromfile(f, dtype=np.float32)

wavfile.write(outwavfile, int(samplerate), data)

print("Done !")