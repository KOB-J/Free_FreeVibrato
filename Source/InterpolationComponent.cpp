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
    interpolationLabel.setFont(juce::Font(12.0f, juce::Font::bold));
    interpolationLabel.setColour(juce::Label::textColourId, white);

    nearestInterpolation.setButtonText("Nearest");
    linearInterpolation.setButtonText("Linear");
    cubicInterpolation.setButtonText("Cubic");

    nearestInterpolation.setColour(juce::TextButton::buttonColourId, darkYellow);
    nearestInterpolation.setColour(juce::TextButton::textColourOffId, black);

    linearInterpolation.setColour(juce::TextButton::buttonColourId, buttonHighlightedColor);
    cubicInterpolation.setColour(juce::TextButton::buttonColourId, buttonHighlightedColor);

    nearestInterpolation.onClick = [this] {buttonClicked(0.0f); };
    linearInterpolation.onClick = [this] {buttonClicked(0.5f); };
    cubicInterpolation.onClick = [this] {buttonClicked(1.0f); };
}

InterpolationComponent::~InterpolationComponent()
{
    audioProcessor.getApvts()->removeParameterListener(juce::StringRef("Interpolation"), this);
}

void InterpolationComponent::paint(juce::Graphics& g) 
{
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
        getButton(selectedButton)->setColour(juce::TextButton::buttonColourId, buttonHighlightedColor);
        getButton(selectedButton)->setColour(juce::TextButton::textColourOffId, white);

        getButton(buttonNumber)->setColour(juce::TextButton::buttonColourId, darkYellow);
        getButton(buttonNumber)->setColour(juce::TextButton::textColourOffId, black);

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