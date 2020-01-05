//
// Created by Thomas Hezard on 2019/01/28
//

#ifndef IOS_AUDIO_PROCESSOR_AUDIO_PROCESSOR_H
#define IOS_AUDIO_PROCESSOR_AUDIO_PROCESSOR_H


#import <atomic>


class AudioProcessor {

    public:

    // Constructors and destructors
    AudioProcessor(); // default constructor with gain = 1.0
    AudioProcessor(float gain);
    ~AudioProcessor() = default;

    // Setters and getters
    // - param_id 0 : gain
    void set_param(int param_id, float value);
    float get_param(int param_id);

    // Process
    void Process(float * io_buffer, int number_frames);

    private:
    // persistent data members
    // ex: float        sampleRate;
    std::atomic<float> gain_;
    // internal setters and getters
    void set_gain(float gain);
    float gain();
    // pre-allocated memory
    // ex: | float *    memoryBuffer;
    //     | int        memoryBufferLength;

};


#endif //IOS_AUDIO_PROCESSOR_AUDIO_PROCESSOR_H
