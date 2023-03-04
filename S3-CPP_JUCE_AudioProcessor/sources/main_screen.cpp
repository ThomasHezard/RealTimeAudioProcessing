/*
  ==============================================================================

    MainScreen.cpp
    Created: 1 Sep 2021 6:24:13pm
    Author:  Thomas Hézard

  ==============================================================================
*/

#include "main_screen.h"

MainScreen::MainScreen()
{    
    openGLContext.attachTo (*getTopLevelComponent());
    
    addAndMakeVisible (&openButton_);
    openButton_.setButtonText ("Open...");
    openButton_.onClick = [this] { openButtonClicked(); };

    addAndMakeVisible (&playButton_);
    playButton_.setButtonText ("Play");
    playButton_.onClick = [this] { 
        playButton_.setEnabled(false);
        stopButton_.setEnabled(true);
        if (onPlayButtonClicked != nullptr) 
            onPlayButtonClicked(); 
    };
    playButton_.setColour (juce::TextButton::buttonColourId, juce::Colours::green);
    playButton_.setEnabled (false);

    addAndMakeVisible (&stopButton_);
    stopButton_.setButtonText ("Stop");
    stopButton_.onClick = [this] { 
        playButton_.setEnabled(true);
        stopButton_.setEnabled(false);
        if (onStopButtonClicked != nullptr) 
            onStopButtonClicked();
    };
    stopButton_.setColour (juce::TextButton::buttonColourId, juce::Colours::red);
    stopButton_.setEnabled (false);
    
    addAndMakeVisible(&sliderA_);
    sliderA_.setRange({0, 1}, 0.001);
    sliderA_.setValue(0.5);
    sliderA_.onValueChange = [&]() {
        if (onSliderAChanged != nullptr)
            onSliderAChanged(sliderA_.getValue());
    };
    sliderA_.setSkewFactorFromMidPoint(0.5);
    sliderA_.setTextValueSuffix("");
    sliderA_.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderA_.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::white);
    sliderA_.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour(69, 69, 69));
    sliderA_.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour(232, 232, 232));
    
    addAndMakeVisible(&labelA_);
    labelA_.setText("Param A", juce::dontSendNotification);
    labelA_.setJustificationType(juce::Justification::centred);
    labelA_.attachToComponent(&sliderA_, false);
        
    addAndMakeVisible(&sliderB_);
    sliderB_.setRange({0, 1}, 0.001);
    sliderB_.setValue(0.5);
    sliderB_.onValueChange = [&]() {
        if (onSliderBChanged != nullptr)
            onSliderBChanged(sliderB_.getValue());
    };
    sliderB_.setTextValueSuffix("");
    sliderB_.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sliderB_.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::white);
    sliderB_.setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, juce::Colour(69, 69, 69));
    sliderB_.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colour(232, 232, 232));
    
    addAndMakeVisible(&labelB_);
    labelB_.setText("Param B", juce::dontSendNotification);
    labelB_.setJustificationType(juce::Justification::centred);
    labelB_.attachToComponent(&sliderB_, false);

}

MainScreen::~MainScreen()
{
    openGLContext.detach();
}

void MainScreen::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour(21, 28, 31));
}

void MainScreen::resized()
{
    openButton_.setBounds(0, 0, getWidth()/3, getHeight()/10);
    playButton_.setBounds(getWidth()/3, 0, getWidth()/3, getHeight()/10);
    stopButton_.setBounds(2*getWidth()/3, 0, getWidth()/3, getHeight()/10);
    
    sliderA_.setSize(getWidth()/2, getHeight()/2);
    sliderA_.setCentrePosition(getWidth()/4, getHeight()/2);
    sliderA_.setTextBoxStyle(juce::Slider::TextBoxBelow, true, sliderA_.getWidth()/4, sliderA_.getHeight()/8);
    
    sliderB_.setSize(getWidth()/2, getHeight()/2);
    sliderB_.setCentrePosition(3*getWidth()/4, getHeight()/2);
    sliderB_.setTextBoxStyle(juce::Slider::TextBoxBelow, true, sliderB_.getWidth()/4, sliderB_.getHeight()/8);
}

void MainScreen::setPlayButtonEnabled(bool enabled)
{
    playButton_.setEnabled(enabled);
}

void MainScreen::setStopButtonEnabled(bool enabled)
{
    stopButton_.setEnabled(enabled);
}

void MainScreen::openButtonClicked()
{
    juce::FileChooser chooser ("Select a mp3 or wav file to play...",
                               {},
                               "*.mp3;*.wav");
    
    if (chooser.browseForFileToOpen())
    {
        auto file = chooser.getResult();
        if (onAudioFileChoosed != nullptr)
            onAudioFileChoosed(file);
    }
}
