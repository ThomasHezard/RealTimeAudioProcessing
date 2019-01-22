import numpy as np
import scipy.io.wavfile as wavfile
import sys

inwavfile = sys.argv[1]
outpcmfile = sys.argv[2]

print("Converting wav file {} to mono-downmix pcm float32 file {}...".format(inwavfile, outpcmfile))

fs, input_data = wavfile.read(inwavfile, mmap=True)
max_value = float(-np.iinfo(input_data.dtype).min)
input_data = input_data.astype('float32') / max_value
if len(input_data.shape) > 1:
    input_data = np.mean(input_data, axis=1)
input_data = input_data.flatten()

data_array = np.array(input_data)

output_file = open(outpcmfile, 'wb')
data_array.tofile(output_file)

print("Done !")