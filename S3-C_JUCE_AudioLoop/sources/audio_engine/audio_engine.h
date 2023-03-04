/*
  ==============================================================================

    AudioEngine.h
    Created: 1 Sep 2021 6:24:22pm
    Author:  Thomas Hézard

  ==============================================================================
*/

#pragma once

#include "audio_processor.h"


class AudioEngine {
    
public:
    
    // =========================================
    // CONSTRUCTOR & DESTRUCTOR
    
    /// Constructor
    AudioEngine();
    
    /// Destructor
    ~AudioEngine();
    
    // =========================================
    // AUDIO LIFE CYCLE
    
    /// Prepare resources
    /// Inform audio modules of samples per block and sample rate values, 
    /// so that they can prepare (allocate buffers etc.) their resources
    /// to get ready to generate/process audio data.
    /// @param maxSamplesPerBlock Max value of `numSamples` in a `generateAudioData` call.
    /// @param sampleRate Sample rate of audio data.
    void prepareResources(int maxSamplesPerBlock, double sampleRate);
    
    /// Release resources
    /// Inform audio modules that they can release their resources before
    /// the app terminates or before a change in sample rate or samples 
    /// per block values.
    void releaseResources();
    
    /// Process a block of audio data.
    /// @param ioAudioData Audio buffer to process, 2D array of size [numChannels, numSamples].
    /// @param inputNumChannels Number of input channels.
    /// @param outputNumChannels Number of output channels.
    /// @param numSamples Number of samples in each channel.
    void processAudioData(float*const* ioAudioData, 
                          int inputNumChannels,
                          int outputNumChannels,
                          int numSamples);
    
    // =========================================
    // CONTROLS
    
    /// Set the parameter A
    /// @param parameter New value of the parameter.
    void setParameterA(float parameter);
    
    /// Return the value of the parameter A
    float getParameterA() const;
    
    /// Set the parameter B
    /// @param parameter New value of the parameter.
    void setParameterB(float parameter);
    
    /// Return the value of the parameter B
    float getParameterB() const;
    
private:
    AudioProcessor* audio_processor_;
    float parameter_a_;
    float parameter_b_;
};
