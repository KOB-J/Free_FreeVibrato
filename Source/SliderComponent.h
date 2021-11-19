/*
  ==============================================================================

    SliderComponent.h
    Created: 19 Nov 2021 10:17:29am
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Constants.h"
#include "PluginProcessor.h"


class SliderComponent 
    : public juce::Component
{
public:
    SliderComponent(FreeVibratoAudioProcessor& p)
        : audioProcessor(p)
    {
        addAndMakeVisible(sweepWidthLabel);
        addAndMakeVisible(lfoFrequencyLabel);
        addAndMakeVisible(sweepWidthValue);
        addAndMakeVisible(lfoFrequencyValue);

        sweepWidthLabel.setText("Sweep Width:", juce::dontSendNotification);
        lfoFrequencyLabel.setText("LFO Frequency:", juce::dontSendNotification);
        sweepWidthLabel.setFont(juce::Font(12.0f, juce::Font::italic));
        lfoFrequencyLabel.setFont(juce::Font(12.0f, juce::Font::italic));
        sweepWidthValue.setFont(juce::Font(12.0f, juce::Font::italic));
        lfoFrequencyValue.setFont(juce::Font(12.0f, juce::Font::italic));
    }

    ~SliderComponent()
    {
    }

    void resized() override
    {
        sweepWidthLabel.setBounds(15, 15, 100, 10);
        lfoFrequencyLabel.setBounds(165, 15, 100, 10);
        sweepWidthValue.setBounds(15, 90, 100, 10);
        lfoFrequencyValue.setBounds(165, 90, 100, 10);
    }

    juce::Label* getSweepWidthValue() { return &sweepWidthValue; }
    juce::Label* getLfoFrequencyValue() { return &lfoFrequencyValue; }

private:
    FreeVibratoAudioProcessor& audioProcessor;

    juce::Label sweepWidthLabel, lfoFrequencyLabel, sweepWidthValue, lfoFrequencyValue;
};