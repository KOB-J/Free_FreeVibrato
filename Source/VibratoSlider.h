/*
  ==============================================================================

    VibratoSlider.h
    Created: 15 Nov 2021 6:24:21am
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "VibratoSliderLookAndFeel.h"

class VibratoSlider : public juce::Slider
{
public:
    VibratoSlider();
    ~VibratoSlider();

private:
    VibratoSliderLookAndFeel vibratoSliderLookAndFeel;
};
