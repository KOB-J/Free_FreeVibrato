/*
  ==============================================================================

    VibratoComboBox.h
    Created: 15 Nov 2021 9:43:10am
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Constants.h"

class VibratoComboBox : public juce::ComboBox
{
public:
    VibratoComboBox()
    {
        setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::aliceblue);
        setColour(juce::ComboBox::ColourIds::backgroundColourId, pluginColor);

        juce::StringArray presetsArray = {"preset1", "preset2", "preset3", "preset4"};
        addItemList(presetsArray, 1);
    }

    ~VibratoComboBox()
    {

    }

private:

};