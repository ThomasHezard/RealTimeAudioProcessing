//
// Created by Thomas Hezard on 2019/01/28
//

#include "audio_processor.h"
#include <stdlib.h>
#include <assert.h>


// alloc an AudioProcessor
AudioProcessor* new_audio_processor() {

    AudioProcessor* newProcessor = (AudioProcessor*)calloc(1,sizeof(AudioProcessor));
    return newProcessor;
}


// initialize all data members, pre-allocate memory if needed
void prepare_audio_processor(AudioProcessor* processor) {
    
}


// free AudioProcessor and its allocated members if needed
void destroy_audio_processor(AudioProcessor* processor) {

    free(processor);
}


// process function, plug it to your main audio signal process flow
void ap_process(AudioProcessor* processor, float* input_buffer, float* output_buffer, int number_frames) {

    assert(number_frames >= 0);
    for (int i=0; i<number_frames; ++i) {
        output_buffer[i] = input_buffer[i];
    }
}
