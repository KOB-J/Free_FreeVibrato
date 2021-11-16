/*
  ==============================================================================

    InterpolationComponent.h
    Created: 15 Nov 2021 4:31:32pm
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class InterpolationComponent : public juce::Component 
{
public:
    InterpolationComponent()
    {
        addAndMakeVisible(interpolationLabel);
        addAndMakeVisible(nearestInterpolation);
        addAndMakeVisible(linearInterpolation);
        addAndMakeVisible(cubicInterpolation);

        interpolationLabel.setText("Interpolation:", juce::dontSendNotification);
        nearestInterpolation.setButtonText("Nearest");
        linearInterpolation.setButtonText("Linear");
        cubicInterpolation.setButtonText("Cubic");

        nearestInterpolation.setColour(juce::TextButton::buttonColourId, pluginColor);
    }

    ~InterpolationComponent()
    {}

    void paint(juce::Graphics& g) override
    {
        g.setColour(juce::Colours::white);
        //g.fillRoundedRectangle(100, 100, 100, 100, 10);// getBounds().toFloat(), 10.0f);
        //g.drawText("test", 50, 50, 50, 50, juce::Justification::centred);
       
        //g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 10, 4);
    }

    void resized() override
    {
        auto stepAhead = getHeight() * 0.25f;
        interpolationLabel.setBounds(getX(), getY(), getWidth(), stepAhead);
        nearestInterpolation.setBounds(getX(), stepAhead, getWidth(), stepAhead);
        linearInterpolation.setBounds(getX(), stepAhead * 2, getWidth(), stepAhead);
        cubicInterpolation.setBounds(getX(), stepAhead * 3, getWidth(), stepAhead);
    }

private:
    juce::Label interpolationLabel;
    juce::TextButton nearestInterpolation, linearInterpolation, cubicInterpolation;
};