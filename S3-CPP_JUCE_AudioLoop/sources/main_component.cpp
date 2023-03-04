#include "main_component.h"

//==============================================================================
MainComponent::MainComponent()
#if (!(JUCE_ANDROID || JUCE_IOS))
: 
audioDeviceSelector_(deviceManager, 0, 2, 0, 2, false, false, false, true)
#endif
{    
    addAndMakeVisible(&mainScreen_);
    mainScreen_.onSliderAChanged = [&](float param) { 
        audioEngine_.setParameterA(param);         
    };
    mainScreen_.onSliderBChanged = [&](float param) { 
        audioEngine_.setParameterB(param); 
    };
    
#if (!(JUCE_ANDROID || JUCE_IOS))
    addAndMakeVisible(&audioDeviceSelector_);
#endif
    
    setSize (900, 300);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (1, 2);
    }
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
#if (JUCE_ANDROID || JUCE_IOS)
    mainScreen_.setBounds(getBounds());
#else
    audioDeviceSelector_.setBounds(0, 0, getWidth()/3, getHeight());
    mainScreen_.setBounds(getWidth()/3, 0, 2*getWidth()/3, getHeight());
#endif
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    audioEngine_.prepareResources(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto buffer = *bufferToFill.buffer;
    audioEngine_.processAudioData(buffer.getArrayOfWritePointers(), 1, 2,  buffer.getNumSamples());
}

void MainComponent::releaseResources()
{
    audioEngine_.releaseResources();
}
