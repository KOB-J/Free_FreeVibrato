/*
  ==============================================================================

    VibratoComboBox.h
    Created: 15 Nov 2021 9:43:10am
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Constants.h"


class VibratoComboBox 
    : public juce::ComboBox
    , public juce::AudioProcessorValueTreeState::Listener
{
public:
    VibratoComboBox(FreeVibratoAudioProcessor& p)
        : audioProcessor(p)
    {
        selectedId = 1;

        p.getApvts()->addParameterListener(juce::StringRef("sweepWidth"), this);
        p.getApvts()->addParameterListener(juce::StringRef("lfoFrequency"), this);
        p.getApvts()->addParameterListener(juce::StringRef("Waveforms"), this);
        p.getApvts()->addParameterListener(juce::StringRef("Interpolation"), this);

        setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::aliceblue);
        setColour(juce::ComboBox::ColourIds::backgroundColourId, pluginBackgroundColor);

        juce::StringArray presetsArray = {"  ", "preset 1", "preset 2", "preset 3", "preset 4"};
        addItemList(presetsArray, 1);

        onChange = [this] { updateApvtsWithPreset(); };
    }

    ~VibratoComboBox()
    {

    }

    void parameterChanged(const juce::String& parameterID, float newValue) override
    {
        if (selectedId != 1)
        {
            setSelectedId(0, juce::dontSendNotification);
            selectedId = 1;
        }
    }

    void updateApvtsWithPreset()
    {
        switch (getSelectedId())
        {
        case 2: {
            audioProcessor.getApvts()->getParameter(juce::StringRef("sweepWidth"))->setValueNotifyingHost(0.15f);
            audioProcessor.getApvts()->getParameter(juce::StringRef("lfoFrequency"))->setValueNotifyingHost(0.5f);
            audioProcessor.getApvts()->getParameter(juce::StringRef("Waveforms"))->setValueNotifyingHost(0.0f);
            audioProcessor.getApvts()->getParameter(juce::StringRef("Interpolation"))->setValueNotifyingHost(0.0f);
            selectedId = 2;
            break;
        }
        case 3: {
            audioProcessor.getApvts()->getParameter(juce::StringRef("sweepWidth"))->setValueNotifyingHost(0.01f);
            audioProcessor.getApvts()->getParameter(juce::StringRef("lfoFrequency"))->setValueNotifyingHost(0.2f);
            audioProcessor.getApvts()->getParameter(juce::StringRef("Waveforms"))->setValueNotifyingHost(0.25f);
            audioProcessor.getApvts()->getParameter(juce::StringRef("Interpolation"))->setValueNotifyingHost(0.5f);
            selectedId = 3;
            break;
        }
        case 4: {
            audioProcessor.getApvts()->getParameter(juce::StringRef("sweepWidth"))->setValueNotifyingHost(0.1f);
            audioProcessor.getApvts()->getParameter(juce::StringRef("lfoFrequency"))->setValueNotifyingHost(0.35f);
            audioProcessor.getApvts()->getParameter(juce::StringRef("Waveforms"))->setValueNotifyingHost(0.5f);
            audioProcessor.getApvts()->getParameter(juce::StringRef("Interpolation"))->setValueNotifyingHost(1.0f);
            selectedId = 4;
            break;
        }
        case 5: 
            audioProcessor.getApvts()->getParameter(juce::StringRef("sweepWidth"))->setValueNotifyingHost(0.7f);
            audioProcessor.getApvts()->getParameter(juce::StringRef("lfoFrequency"))->setValueNotifyingHost(0.8f);
            audioProcessor.getApvts()->getParameter(juce::StringRef("Waveforms"))->setValueNotifyingHost(0.75f);
            audioProcessor.getApvts()->getParameter(juce::StringRef("Interpolation"))->setValueNotifyingHost(0.5f);
            selectedId = 5;
            break;

        default: 
            break;
        }
    }

private:
    FreeVibratoAudioProcessor& audioProcessor;

    int selectedId;
};