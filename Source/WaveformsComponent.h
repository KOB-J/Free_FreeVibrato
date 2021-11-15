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

        addAndMakeVisible(sineButton);
        addAndMakeVisible(triangleButton);
        addAndMakeVisible(squareButton);
        addAndMakeVisible(sawtoothButton);
        addAndMakeVisible(inverseSawtoothButton);

    }

    ~WaveformsComponent()
    {

    }

    void resized() override
    {
        waveformsLabel.setBounds(getX(), getY(), getWidth(), getHeight() / 2);

        int margin = getX();
        sineButton.setBounds(margin, getHeight() / 3, getWidth() / 5, getHeight() / 3);
        margin += getWidth() / 5;
        triangleButton.setBounds(margin, getHeight() / 3, getWidth() / 5, getHeight() / 3);
        margin += getWidth() / 5;
        squareButton.setBounds(margin, getHeight() / 3, getWidth()  / 5, getHeight() / 3);
        margin += getWidth() / 5;
        sawtoothButton.setBounds(margin, getHeight() / 3, getWidth()  / 5, getHeight() / 3);
        margin += getWidth() / 5;
        inverseSawtoothButton.setBounds(margin, getHeight() / 3, getWidth() / 5, getHeight() / 3);

    }

private:

    juce::Label waveformsLabel;
    juce::TextButton sineButton, triangleButton, squareButton, sawtoothButton, inverseSawtoothButton;
};
