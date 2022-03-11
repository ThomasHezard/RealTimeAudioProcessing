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

AudioEngine::AudioEngine() : audio_processor_{}, parameter_a_{0.0f}, parameter_b_{0.0f}
{
    player_.didPlay = [&]() { 
        if (didPlay != nullptr)
            didPlay();
    };
    
    player_.didStop = [&]() { 
        if (didStop != nullptr)
            didStop();
    };
}

void AudioEngine::prepareResources(int maxSamplesPerBlock, double sampleRate)
{
    player_.prepareResources(maxSamplesPerBlock, sampleRate);
    audio_processor_.Prepare();
}

void AudioEngine::releaseResources()
{
    player_.releaseResources();
}

void AudioEngine::generateAudioData(float **outputAudioData, int outputNumChannels, int numSamples)
{
    assert(outputNumChannels == 2);
    
    player_.generateAudioData(outputAudioData, outputNumChannels, numSamples);
    for (int i = 0; i<numSamples; ++i) {
        outputAudioData[0][i] = sqrtf(2.0f) / 2.0f * (outputAudioData[0][i] + outputAudioData[1][i]);
    }
    audio_processor_.Process(outputAudioData[0], outputAudioData[0], numSamples);
    memcpy(outputAudioData[1], outputAudioData[0], numSamples*sizeof(float));
}

void AudioEngine::Load(const juce::File &file)
{
    player_.Load(file);
}

void AudioEngine::Play()
{
    player_.Play();
}

void AudioEngine::Stop()
{
    player_.Stop();
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
