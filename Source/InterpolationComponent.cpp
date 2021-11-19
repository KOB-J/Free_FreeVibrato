/*
  ==============================================================================

    InterpolationComponent.cpp
    Created: 16 Nov 2021 3:18:28pm
    Author:  dev

  ==============================================================================
*/

#include "InterpolationComponent.h"


InterpolationComponent::InterpolationComponent(FreeVibratoAudioProcessor& p)
    : audioProcessor(p)
{
    selectedButton = 0.0f;

    p.getApvts()->addParameterListener(juce::StringRef("Interpolation"), this);
    addAndMakeVisible(interpolationLabel);
    addAndMakeVisible(nearestInterpolation);
    addAndMakeVisible(linearInterpolation);
    addAndMakeVisible(cubicInterpolation);

    interpolationLabel.setText("Interpolation:", juce::dontSendNotification);
    nearestInterpolation.setButtonText("Nearest");
    linearInterpolation.setButtonText("Linear");
    cubicInterpolation.setButtonText("Cubic");

    nearestInterpolation.setColour(juce::TextButton::buttonColourId, pluginColor.darker());
    linearInterpolation.setColour(juce::TextButton::buttonColourId, pluginColor);
    cubicInterpolation.setColour(juce::TextButton::buttonColourId, pluginColor);

    nearestInterpolation.onClick = [this] {buttonClicked(0.0f); };
    linearInterpolation.onClick = [this] {buttonClicked(0.5f); };
    cubicInterpolation.onClick = [this] {buttonClicked(1.0f); };

}

InterpolationComponent::~InterpolationComponent()
{}

void InterpolationComponent::paint(juce::Graphics& g) 
{
    g.setColour(juce::Colours::black);
    //g.fillRoundedRectangle(100, 100, 100, 100, 10);// getBounds().toFloat(), 10.0f);

    //g.fillRoundedRectangle(0, 0, getWidth(), getHeight(), 10);

    //g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 10, 1);
}

void InterpolationComponent::resized() 
{
    auto stepAhead = getHeight() * 0.25f;
    auto margin = 4;

    interpolationLabel.setBounds(getX() + margin, getY(), getWidth() - margin * 2, stepAhead - margin - 2);
    nearestInterpolation.setBounds(getX() + margin, stepAhead, getWidth() - margin * 2, stepAhead - margin);
    linearInterpolation.setBounds(getX() + margin, stepAhead * 2, getWidth() - margin * 2, stepAhead - margin);
    cubicInterpolation.setBounds(getX() + margin, stepAhead * 3, getWidth() - margin * 2, stepAhead - margin);
}

void InterpolationComponent::parameterChanged(const juce::String& parameterID, float newValue) 
{
    DBG("it does work! parameterID= " << parameterID << " newValue= " << newValue);
    if (selectedButton != newValue) highlightSelectedButton(newValue);
}

void InterpolationComponent::buttonClicked(float buttonNumber)
{
    highlightSelectedButton(buttonNumber);
    audioProcessor.getApvts()->getParameter(juce::StringRef("Interpolation"))->setValueNotifyingHost(buttonNumber);
}

void InterpolationComponent::highlightSelectedButton(float buttonNumber)
{
    if (selectedButton != buttonNumber)
    {
        getButton(selectedButton)->setColour(juce::TextButton::buttonColourId, pluginColor);
        getButton(buttonNumber)->setColour(juce::TextButton::buttonColourId, pluginColor.darker());
        selectedButton = buttonNumber;
    }
}

juce::TextButton* InterpolationComponent::getButton(float buttonNumber)
{
    switch ((int)buttonNumber)
    {
    case 0: return &nearestInterpolation;
        break;
    case 1: return &linearInterpolation;
        break;
    case 2: return &cubicInterpolation;
        break;
    default:
        break;
    }
}