# /// script
# requires-python = ">=3.7"
# dependencies = ["numpy", "scipy"]
# ///

import os
import numpy as np
import scipy.io.wavfile as wavfile

_dir = os.path.dirname(os.path.abspath(__file__))

# Parameters
# **********

# Input audio file must be readable by scipy.io.wavfile.read() function
input_file = os.path.join(_dir, 'Marimba.wav')
output_file = os.path.join(_dir, 'output.wav')


# Read input file
# ***************

fs, input_data = wavfile.read(input_file, mmap=True)
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
output_data = 0.99 * output_data / max(abs(output_data))
wavfile.write(output_file, int(fs), (output_data*np.iinfo(np.int16).max).astype(np.int16))
