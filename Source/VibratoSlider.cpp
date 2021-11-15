/*
  ==============================================================================

    VibratoSlider.cpp
    Created: 15 Nov 2021 6:24:21am
    Author:  dev

  ==============================================================================
*/

#include "VibratoSlider.h"

VibratoSlider::VibratoSlider()
{
    float twoPi = juce::MathConstants<float>::twoPi;

    setSliderStyle(juce::Slider::RotaryVerticalDrag);
    setLookAndFeel(&vibratoSliderLookAndFeel);
    setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    setRange(0.0f, 1.0f, 0.01f);
    //setNormalisableRange(juce::NormalisableRange<double>(0.0, 1.0, 0.1));
    //setRotaryParameters(0.0f, twoPi, true);
}

VibratoSlider::~VibratoSlider()
{
    setLookAndFeel(nullptr);
}
