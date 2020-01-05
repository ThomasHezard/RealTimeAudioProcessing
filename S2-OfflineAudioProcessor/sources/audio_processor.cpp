//
// Created by Thomas Hezard on 2019/01/28
//

#include "audio_processor.h"
#include <assert.h>


AudioProcessor::AudioProcessor() {
}

void AudioProcessor::Process(float* input_buffer, float* output_buffer, int number_frames) {
    assert(number_frames >= 0);
    for (int i=0; i<number_frames; ++i) {
        output_buffer[i] = input_buffer[i];
    }
}