/*
  ==============================================================================

    WaveformsComponent.h
    Created: 15 Nov 2021 12:04:54pm
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class WaveformsComponent : public juce::Component
{
public:
    WaveformsComponent()
    {
        addAndMakeVisible(waveformsLabel);
        waveformsLabel.setText("Waveforms:", juce::dontSendNotification);
    }

    ~WaveformsComponent()
    {

    }

    void resized() override
    {
        waveformsLabel.setBounds(getX(), getY(), getWidth(), getHeight() / 2);
    }

private:

    juce::Label waveformsLabel;
    juce::ImageButton sineButton, triangleButton, squareButton, sawtoothButton, inverseSawtoothButton;
};
