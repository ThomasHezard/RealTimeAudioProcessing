/*
  ==============================================================================

    AudioEngine.h
    Created: 1 Sep 2021 6:24:22pm
    Author:  Thomas Hézard

  ==============================================================================
*/

#pragma once

#include "audio_processor.h"
#include "audio_file_player.h"


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
    
    /// Generate a block of audio data.
    /// @param outputAudioData Audio buffer to fill, 2D array of size [numChannels, numSamples].
    /// @param numChannels Number of channels.
    /// @param numSamples Number of samples in each channel.
    void generateAudioData(float*const* outputAudioData, 
                           int numChannels, 
                           int numSamples);
    
    // =========================================
    // FILE PLAYER
    
    /// Loads an audio file.
    void Load(const juce::File& file);
        
    /// Starts the playback of the audio file (if a file has been loaded).
    void Play();
    
    /// You can assign a lambda to this callback object to have it called when the playback has started.
    std::function<void()> didPlay;
    
    /// Stops the playback of the audio file.
    void Stop();
    
    /// You can assign a lambda to this callback object to have it called when the playback has stopped.
    /// Note that didStop can be called when you call Stop() or when playback reaches the end of the audio file. 
    std::function<void()> didStop;
    
    // =========================================
    // PARAMETERS CONTROLS
    
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
    AudioFilePlayer player_;
    AudioProcessor* audio_processor_;
    float parameter_a_;
    float parameter_b_;
};
