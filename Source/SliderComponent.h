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
    , public juce::AudioProcessorValueTreeState::Listener
{
public:
    SliderComponent(FreeVibratoAudioProcessor& p)
        : audioProcessor(p)
    {
        p.getApvts()->addParameterListener(juce::StringRef("sweepWidth"), this);
        p.getApvts()->addParameterListener(juce::StringRef("lfoFrequency"), this);

        addAndMakeVisible(sweepWidthLabel);
        addAndMakeVisible(lfoFrequencyLabel);
        addAndMakeVisible(sweepWidthValue);
        addAndMakeVisible(lfoFrequencyValue);

        sweepWidthLabel.setText("Sweep Width:", juce::dontSendNotification);
        lfoFrequencyLabel.setText("LFO Frequency:", juce::dontSendNotification);
        sweepWidthLabel.setFont(juce::Font(12.0f, juce::Font::italic));
        lfoFrequencyLabel.setFont(juce::Font(12.0f, juce::Font::italic));

    }

    ~SliderComponent()
    {
        audioProcessor.getApvts()->addParameterListener(juce::StringRef("sweepWidth"), this);
        audioProcessor.getApvts()->addParameterListener(juce::StringRef("lfoFrequency"), this);
    }

    void paint(juce::Graphics& g) override
    {
        //g.fillAll(juce::Colours::black);
    }

    void resized() override
    {
        sweepWidthLabel.setBounds(15, 15, 100, 10);
        lfoFrequencyLabel.setBounds(165, 15, 100, 10);
        sweepWidthValue.setBounds(15, 90, 100, 10);
        lfoFrequencyValue.setBounds(165, 90, 100, 10);
    }

    void parameterChanged(const juce::String& parameterID, float newValue) override
    {
        DBG("SliderComponent, slider value: " << newValue);

        if (parameterID == "sweepWidth")
        {
            auto value = newValue * 1000;
            sweepWidthValue.setText(juce::String(value), juce::dontSendNotification);
        }

        if (parameterID == "lfoFrequency")
        {
            auto value = newValue;
            lfoFrequencyValue.setText(juce::String(value), juce::dontSendNotification);
        }
    }

private:
    FreeVibratoAudioProcessor& audioProcessor;

    juce::Label sweepWidthLabel, lfoFrequencyLabel, sweepWidthValue, lfoFrequencyValue;
};