#include "main_component.h"

//==============================================================================
MainComponent::MainComponent()
{    
    addAndMakeVisible(&mainScreen_);
    
    mainScreen_.onSliderAChanged = [&](float param) { 
        audioEngine_.setParameterA(param);         
    };
    mainScreen_.onSliderBChanged = [&](float param) { 
        audioEngine_.setParameterB(param); 
    };
    
    mainScreen_.onAudioFileChoosed = [&](const juce::File& file) {
        audioEngine_.Load(file);
        mainScreen_.setPlayButtonEnabled(true);
    };
    
    mainScreen_.onPlayButtonClicked = [&]() {
        audioEngine_.Play();
    };
    
    mainScreen_.onStopButtonClicked = [&]() {
        audioEngine_.Stop();
    };
    
    audioEngine_.didPlay = [&] {
        mainScreen_.setPlayButtonEnabled(false);
        mainScreen_.setStopButtonEnabled(true);
    };
    
    audioEngine_.didStop = [&] {
        mainScreen_.setPlayButtonEnabled(true);
        mainScreen_.setStopButtonEnabled(false);
    };
    
    setSize (900, 300);

    setAudioChannels (0, 2);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    mainScreen_.paint(g);
}

void MainComponent::resized()
{
    mainScreen_.setBounds(getBounds());
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    audioEngine_.prepareResources(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto buffer = *bufferToFill.buffer;
    audioEngine_.generateAudioData(buffer.getArrayOfWritePointers(), buffer.getNumChannels(), buffer.getNumSamples());
}

void MainComponent::releaseResources()
{
    audioEngine_.releaseResources();
}
