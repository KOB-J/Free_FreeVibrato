/*
  ==============================================================================

    WaveformsComponent.h
    Created: 15 Nov 2021 12:04:54pm
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Constants.h"


class WaveformsComponent 
    : public juce::Component
    , public juce::AudioProcessorValueTreeState::Listener
{
public:
    WaveformsComponent(FreeVibratoAudioProcessor& p);

    ~WaveformsComponent();

    void resized() override;

    void parameterChanged(const juce::String& parameterID, float newValue) override;

    void buttonClicked(float buttonNumber);

    void highlightSelectedButton(float buttonNumber);

private:
    FreeVibratoAudioProcessor& audioProcessor;

    juce::Label waveformsLabel;
    juce::TextButton sineButton, triangleButton, squareButton, sawtoothButton, inverseSawtoothButton;

    float selectedButton;

    juce::TextButton* getButton(float buttonNumber);
};
