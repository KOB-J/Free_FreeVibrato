/*
  ==============================================================================

    WaveformsComponent.cpp
    Created: 16 Nov 2021 3:42:40pm
    Author:  dev

  ==============================================================================
*/

#include "WaveformsComponent.h"


WaveformsComponent::WaveformsComponent(FreeVibratoAudioProcessor& p)
    : audioProcessor(p)
{
    selectedButton = 0.0f;

    p.getApvts()->addParameterListener(juce::StringRef("Waveforms"), this);

    addAndMakeVisible(waveformsLabel);
    waveformsLabel.setText("Waveforms:", juce::dontSendNotification);

    addAndMakeVisible(sineButton);
    addAndMakeVisible(triangleButton);
    addAndMakeVisible(squareButton);
    addAndMakeVisible(sawtoothButton);
    addAndMakeVisible(inverseSawtoothButton);

    sineButton.setColour(juce::TextButton::buttonColourId, pluginColor.darker());
    triangleButton.setColour(juce::TextButton::buttonColourId, pluginColor);
    squareButton.setColour(juce::TextButton::buttonColourId, pluginColor);
    sawtoothButton.setColour(juce::TextButton::buttonColourId, pluginColor);
    inverseSawtoothButton.setColour(juce::TextButton::buttonColourId, pluginColor);

    sineButton.onClick = [this] {buttonClicked(0.0f); };
    triangleButton.onClick = [this] {buttonClicked(0.25f); };
    squareButton.onClick = [this] {buttonClicked(0.5f); };
    sawtoothButton.onClick = [this] {buttonClicked(0.75f); };
    inverseSawtoothButton.onClick = [this] {buttonClicked(1.0f); };
}

WaveformsComponent::~WaveformsComponent()
{

}

void WaveformsComponent::resized() 
{
    waveformsLabel.setBounds(getX(), getY(), getWidth(), getHeight() / 2);

    int margin = getX();
    sineButton.setBounds(margin, getHeight() / 3, getWidth() / 5, getHeight() / 3);
    margin += getWidth() / 5;
    triangleButton.setBounds(margin, getHeight() / 3, getWidth() / 5, getHeight() / 3);
    margin += getWidth() / 5;
    squareButton.setBounds(margin, getHeight() / 3, getWidth() / 5, getHeight() / 3);
    margin += getWidth() / 5;
    sawtoothButton.setBounds(margin, getHeight() / 3, getWidth() / 5, getHeight() / 3);
    margin += getWidth() / 5;
    inverseSawtoothButton.setBounds(margin, getHeight() / 3, getWidth() / 5, getHeight() / 3);

}

void WaveformsComponent::parameterChanged(const juce::String& parameterID, float newValue)
{
    DBG("it does work! parameterID= " << parameterID << " newValue= " << newValue);
    if (selectedButton != newValue) highlightSelectedButton(newValue);
}

void WaveformsComponent::buttonClicked(float buttonNumber)
{
    DBG("Waveforms button clicked!");
    highlightSelectedButton(buttonNumber);
    audioProcessor.getApvts()->getParameter(juce::StringRef("Waveforms"))->setValueNotifyingHost(buttonNumber);
}

void WaveformsComponent::highlightSelectedButton(float buttonNumber)
{
    if (selectedButton != buttonNumber)
    {
        getButton(selectedButton)->setColour(juce::TextButton::buttonColourId, pluginColor);
        getButton(buttonNumber)->setColour(juce::TextButton::buttonColourId, pluginColor.darker());
        selectedButton = buttonNumber;
    }
}

juce::TextButton* WaveformsComponent::getButton(float buttonNumber)
{
    switch ((int)buttonNumber)
    {
    case 0: return &sineButton;
        break;
    case 1: return &triangleButton;
        break;
    case 2: return &squareButton;
        break;
    case 3: return &sawtoothButton;
        break;
    case 4: return &inverseSawtoothButton;
        break;
    default:
        break;
    }
}
