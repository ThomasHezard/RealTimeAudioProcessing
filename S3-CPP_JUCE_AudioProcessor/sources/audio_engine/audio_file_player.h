//
//  Created by Thomas Hezard on 28/07/2021.
//


#include <JuceHeader.h>

/// An audio file player.
class AudioFilePlayer : public juce::ChangeListener
{
public:
        
    /// Constructor.
    AudioFilePlayer();
    
    // Prepare resources
    // Inform audio modules of samples per block and sample rate values, 
    // so that they can prepare (allocate buffers etc.) their resources
    // to get ready to generate/process audio data.
    void prepareResources(int maxSamplesPerBlock, double sampleRate);
    
    // Release resources
    // Inform audio modules that they can release their resources before
    // the app terminates or before a change in sample rate or samples 
    // per block values.
    void releaseResources();
    
    /// Generates audio data.
    /// @param channelData An array of pointers to the channels of the audio buffer.
    /// @param numChannels The number of channels of the audio buffer.
    /// @param numSamples The number of samples of the audio buffer.
    void generateAudioData(float*const* channelData, 
                           int numChannels, 
                           int numSamples);
        
    /// Loads an audio file.
    void Load(const juce::File& file);
    
    /// Loads an input stream.
    void Load(juce::AudioFormatReader& reader);
            
    /// Starts the playback of the audio file (if a file has been loaded).
    void Play();
    
    /// You can assign a lambda to this callback object to have it called when the playback has started.
    std::function<void()> didPlay;
    
    /// Stops the playback of the audio file.
    void Stop();
    
    /// You can assign a lambda to this callback object to have it called when the playback has stopped.
    /// Note that didStop can be called when you call Stop() or when the playback reaches the end of the audio file. 
    std::function<void()> didStop;
    
    enum State
    {
        kIdle,
        kStopped,
        kPlaying
    };
    
    /// Returns the current state of the audio file player.
    State getState() const;
                
private:
    
    juce::AudioFormatManager formatManager_;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource_;
    juce::AudioTransportSource transportSource_;
    State state_;
    juce::TimeSliceThread backgroundThread_;
    
    void changeListenerCallback (juce::ChangeBroadcaster* source) override;
    
};
