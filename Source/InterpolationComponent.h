/*
  ==============================================================================

    InterpolationComponent.h
    Created: 15 Nov 2021 4:31:32pm
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Constants.h"

class InterpolationComponent 
    : public juce::Component 
    , public juce::AudioProcessorValueTreeState::Listener
{
public:
    InterpolationComponent(FreeVibratoAudioProcessor& p);

    ~InterpolationComponent();

    void paint(juce::Graphics& g) override;

    void resized() override;

    void parameterChanged(const juce::String& parameterID, float newValue) override;

    void buttonClicked(float buttonNumber);

    void highlightSelectedButton(float buttonNumber);

private:
    FreeVibratoAudioProcessor& audioProcessor;

    juce::Label interpolationLabel;
    juce::TextButton nearestInterpolation, linearInterpolation, cubicInterpolation;

    float selectedButton;

    juce::TextButton* getButton(float buttonNumber);
};