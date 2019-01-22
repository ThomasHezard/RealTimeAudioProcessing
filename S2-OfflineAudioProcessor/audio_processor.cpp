//
// Created by Thomas Hezard on 2019/01/28
//

#include "audio_processor.h"
#include <assert.h>


AudioProcessor::AudioProcessor(float gain) {
    if (gain < 0.0f) {
        gain = 0.0f;
    }
    if (gain > 1.0f) {
        gain = 1.0f;
    }
    gain_ = gain;
}

void AudioProcessor::Process(float * io_buffer, int number_frames) {
    assert(number_frames >= 0);
    for (int i=0; i<number_frames; ++i) {
        io_buffer[i] *= gain_;
    }
}