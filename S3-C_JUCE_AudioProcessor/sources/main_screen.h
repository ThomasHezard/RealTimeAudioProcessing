/*
  ==============================================================================

    MainScreen.h
    Created: 1 Sep 2021 6:24:13pm
    Author:  Thomas Hézard

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class MainScreen  : public juce::Component
{
public:
    MainScreen();
    ~MainScreen() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    std::function<void()> onPlayButtonClicked;
    std::function<void()> onStopButtonClicked;
    std::function<void(const juce::File&)> onAudioFileChoosed;
    
    void setPlayButtonEnabled(bool enabled);
    void setStopButtonEnabled(bool enabled);
    
    std::function<void(float)> onSliderAChanged;
    std::function<void(float)> onSliderBChanged;

private:
    void openButtonClicked();

    juce::TextButton openButton_;
    juce::TextButton playButton_;
    juce::TextButton stopButton_;    

    juce::Slider sliderA_;
    juce::Label labelA_;
    
    juce::Slider sliderB_;
    juce::Label labelB_;
        
    juce::OpenGLContext openGLContext;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainScreen)
};
