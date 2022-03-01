#pragma once

#include <JuceHeader.h>
#include "main_screen.h"
#include "audio_engine.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;
    
    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

private:
    //==============================================================================
    MainScreen mainScreen_;
    AudioEngine audioEngine_;
    
#if (!(JUCE_ANDROID || JUCE_IOS))
    juce::AudioDeviceSelectorComponent audioDeviceSelector_;
#endif

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
