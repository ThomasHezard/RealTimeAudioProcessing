//
// Created by Thomas Hezard on 2019/01/28
//

#ifndef OFFLINE_AUDIO_PROCESSOR_AUDIO_PROCESSOR_H
#define OFFLINE_AUDIO_PROCESSOR_AUDIO_PROCESSOR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AudioProcessor {

    // persistent data members
    // ex: float        sampleRate;
    //
    // pre-allocated memory
    // ex: | float *    memoryBuffer;
    //     | int        memoryBufferLength;

}AudioProcessor;

// alloc an AudioProcessor
AudioProcessor* new_audio_processor();

// initialize all data members, pre-allocate memory if needed
void prepare_audio_processor(AudioProcessor* processor);

// free AudioProcessor and its allocated members if needed
void destroy_audio_processor(AudioProcessor* processor);

// process function, plug it to your main audio signal process flow
void ap_process(AudioProcessor* processor, float* input_buffer, float* output_buffer, int number_frames);

#ifdef __cplusplus
}
#endif

#endif //OFFLINE_AUDIO_PROCESSOR_AUDIO_PROCESSOR_H
