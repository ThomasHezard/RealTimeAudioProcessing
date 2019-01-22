//
// Created by Thomas Hezard on 2019/01/28
//

#ifndef AUDIO_ECHO_AUDIO_PROCESSOR_H
#define AUDIO_ECHO_AUDIO_PROCESSOR_H


class AudioProcessor {

    public:

    // Constructors and destructors
    AudioProcessor(float gain);
    ~AudioProcessor() = default;

    // Process
    void Process(float * io_buffer, int number_frames);

    private:
    // persistent data members
    // ex: float        sampleRate;
    float gain_;
    // pre-allocated memory
    // ex: | float *    memoryBuffer;
    //     | int        memoryBufferLength;

};


#endif //AUDIO_ECHO_AUDIO_PROCESSOR_H
