/*
  ==============================================================================

    VibratoLabel.h
    Created: 15 Nov 2021 7:17:18am
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class VibratoLabel : public juce::Label
{
public:
    VibratoLabel()
    {
        juce::Font labelFont = juce::Font(36.0f, juce::Font::bold | juce::Font::italic);
        setFont(labelFont);
        setText("Vibrato", juce::dontSendNotification);
    }

    ~VibratoLabel()
    {}

private:

};