import numpy as np
import scipy.io.wavfile as wavfile


# Parameters
# **********

# This must be an audio file readable by scipy.io.wavfile.read() function
filename = 'Marimba.wav'


# Read input file
# ***************

fs, input_data = wavfile.read(filename, mmap=True)
# convert to float
max_value = float(-np.iinfo(input_data.dtype).min)
input_data = input_data.astype('float32') / max_value
# convert to mono if not already
if len(input_data.shape) > 1:
    input_data = np.mean(input_data, axis=1)
input_data = input_data.flatten()


# Audio data process
# ******************

output_data = np.zeros(len(input_data))

# *************************
# * PROCESSING COMES HERE *
# *************************

output_data = input_data

# *************************


# Save output
# ***********

wavfile.write('output.wav', int(fs), output_data)