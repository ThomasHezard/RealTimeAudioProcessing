/*
  ==============================================================================

    AudioEngine.cpp
    Created: 1 Sep 2021 6:24:22pm
    Author:  Thomas Hézard

  ==============================================================================
*/

#include "audio_engine.h"
#include <cassert>
#include <cstring>

AudioEngine::~AudioEngine()
{
    destroy_audio_processor(audio_processor_);
    audio_processor_ = nullptr;
}

AudioEngine::AudioEngine() : audio_processor_{nullptr}, parameter_a_{0.0f}, parameter_b_{0.0f}
{
    audio_processor_ = new_audio_processor();
}

void AudioEngine::prepareResources(int maxSamplesPerBlock, double sampleRate)
{
    prepare_audio_processor(audio_processor_);
}

void AudioEngine::releaseResources()
{
    
}

void AudioEngine::processAudioData(float *const*ioAudioData, int inputNumChannels, int outputNumChannels, int numSamples)
{
    
    assert(inputNumChannels == 1);
    assert(outputNumChannels == 2);
    
    ap_process(audio_processor_, ioAudioData[0], ioAudioData[0], numSamples);
    memcpy(ioAudioData[1], ioAudioData[0], numSamples*sizeof(float));
}

void AudioEngine::setParameterA(float parameter)
{
    parameter_a_ = parameter;
}

float AudioEngine::getParameterA() const
{
    return parameter_a_;
}

void AudioEngine::setParameterB(float parameter)
{
    parameter_b_ = parameter;
}

float AudioEngine::getParameterB() const
{
    return parameter_b_;
}
