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
    sliderA_.setSize(getWidth()/2, getHeight()/2);
    sliderA_.setCentrePosition(getWidth()/4, getHeight()/2);
    sliderA_.setTextBoxStyle(juce::Slider::TextBoxBelow, true, sliderA_.getWidth()/4, sliderA_.getHeight()/8);
    
    sliderB_.setSize(getWidth()/2, getHeight()/2);
    sliderB_.setCentrePosition(3*getWidth()/4, getHeight()/2);
    sliderB_.setTextBoxStyle(juce::Slider::TextBoxBelow, true, sliderB_.getWidth()/4, sliderB_.getHeight()/8);
}
