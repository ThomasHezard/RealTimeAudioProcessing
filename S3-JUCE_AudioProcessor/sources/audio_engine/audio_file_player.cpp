//
//  Created by Thomas Hezard on 28/07/2021.
//

#include "audio_file_player.h"

AudioFilePlayer::AudioFilePlayer():
state_(kIdle),
backgroundThread_("backgroundThread")
{
    formatManager_.registerBasicFormats();
    transportSource_.addChangeListener(this);
    backgroundThread_.startThread();
}

void AudioFilePlayer::prepareResources(int maxSamplesPerBlock, double sampleRate)
{
    transportSource_.prepareToPlay(maxSamplesPerBlock, sampleRate);
}

void AudioFilePlayer::releaseResources()
{
    transportSource_.releaseResources();
}

void AudioFilePlayer::generateAudioData(float **channelData, int numChannels, int numSamples)
{
    if (readerSource_.get() == nullptr)
    {
        for (auto channel = 0; channel < numChannels; ++channel)
            memset(channelData[channel], 0, sizeof(float)*numSamples);
        return;
    }
    
    juce::AudioBuffer<float> buffer(channelData, numChannels, numSamples);
    juce::AudioSourceChannelInfo audioSourceChannelInfo(buffer);
    transportSource_.getNextAudioBlock(audioSourceChannelInfo);
}

void AudioFilePlayer::Load(const juce::File &file)
{
    auto* reader = formatManager_.createReaderFor (file);

    if (reader != nullptr)
    {
        Load(*reader);
    }
}

void AudioFilePlayer::Load(juce::AudioFormatReader& reader)
{
    std::unique_ptr<juce::AudioFormatReaderSource> newSource (new juce::AudioFormatReaderSource (&reader, true));
    transportSource_.setSource (newSource.get(), 32768, &backgroundThread_, reader.sampleRate);
    readerSource_.reset (newSource.release());
}

void AudioFilePlayer::Play()
{
    transportSource_.setPosition(0);
    transportSource_.start();
}

void AudioFilePlayer::Stop()
{
    transportSource_.stop();
    transportSource_.setPosition(0.0);
}

AudioFilePlayer::State AudioFilePlayer::getState() const
{
    return state_;
}

void AudioFilePlayer::changeListenerCallback (juce::ChangeBroadcaster* source)
{
    if (source == &transportSource_)
    {
        if (transportSource_.isPlaying()) 
        {
            state_ = kPlaying;
            if (didPlay != nullptr)
                didPlay();
        }
        else
        {
            state_ = kStopped;
            if (didStop != nullptr)
                didStop();
        }
    }
}
