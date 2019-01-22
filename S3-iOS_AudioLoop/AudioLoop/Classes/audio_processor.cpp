//
// Created by Thomas Hezard on 2019/01/28
//

#include "audio_processor.h"
#include <assert.h>


AudioProcessor::AudioProcessor() :AudioProcessor(1.0f) {
}

AudioProcessor::AudioProcessor(float gain) {
    set_gain(gain);
}

void AudioProcessor::set_param(int param_id, float value) {
    switch (param_id) {
        case 0:
            set_gain(value);
            break;
        default:
            break;
    }
}

float AudioProcessor::get_param(int param_id) {
    switch (param_id) {
        case 0:
            return gain();
        default:
            return 0.0f;
    }
}

void AudioProcessor::set_gain(float gain) {
    if (gain < 0.0f) {
        gain = 0.0f;
    }
    if (gain > 1.0f) {
        gain = 1.0f;
    }
    gain_ = gain;
}

float AudioProcessor::gain() {
    return gain_;
}

void AudioProcessor::Process(float * io_buffer, int number_frames) {
    assert(number_frames >= 0);
    for (int i=0; i<number_frames; ++i) {
        io_buffer[i] *= gain_;
    }
}
