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

    sineButton.setToggleState(true, juce::dontSendNotification);

    //sineButton.setColour(juce::TextButton::buttonColourId, pluginColor.darker());
    //triangleButton.setColour(juce::TextButton::buttonColourId, pluginColor);
    //squareButton.setColour(juce::TextButton::buttonColourId, pluginColor);
    //sawtoothButton.setColour(juce::TextButton::buttonColourId, pluginColor);
    //inverseSawtoothButton.setColour(juce::TextButton::buttonColourId, pluginColor);

    sineButton.onClick = [this] {buttonClicked(0.0f); };
    triangleButton.onClick = [this] {buttonClicked(0.25f); };
    squareButton.onClick = [this] {buttonClicked(0.5f); };
    sawtoothButton.onClick = [this] {buttonClicked(0.75f); };
    inverseSawtoothButton.onClick = [this] {buttonClicked(1.0f); };

    createImageButtons();
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
        getButton(selectedButton)->setToggleState(false, juce::dontSendNotification);
        getButton(buttonNumber)->setToggleState(true, juce::dontSendNotification);
        selectedButton = buttonNumber;
    }
}

juce::ImageButton* WaveformsComponent::getButton(float buttonNumber)
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

void WaveformsComponent::createImageButtons()
{
    auto sine = juce::ImageCache::getFromMemory(BinaryData::sine_png, BinaryData::sine_pngSize);
    sineButton.setImages(
        false,
        true,
        true,
        sine,
        1.0f,
        juce::Colours::white,
        sine,
        1.0f,
        juce::Colours::grey,
        sine,
        1.0f,
        juce::Colours::black
    );

    auto square = juce::ImageCache::getFromMemory(BinaryData::square_png, BinaryData::square_pngSize);
    squareButton.setImages(
        false,
        true,
        true,
        square,
        1.0f,
        juce::Colours::white,
        square,
        1.0f,
        juce::Colours::grey,
        square,
        1.0f,
        juce::Colours::black
    );

    auto triangle = juce::ImageCache::getFromMemory(BinaryData::triangle_png, BinaryData::triangle_pngSize);
    triangleButton.setImages(
        false,
        true,
        true,
        triangle,
        1.0f,
        juce::Colours::white,
        triangle,
        1.0f,
        juce::Colours::grey,
        triangle,
        1.0f,
        juce::Colours::black
    );

    auto sawtooth = juce::ImageCache::getFromMemory(BinaryData::sawtooth_png, BinaryData::sawtooth_pngSize);
    sawtoothButton.setImages(
        false,
        true,
        true,
        sawtooth,
        1.0f,
        juce::Colours::white,
        sawtooth,
        1.0f,
        juce::Colours::grey,
        sawtooth,
        1.0f,
        juce::Colours::black
    );

    auto inverse_sawtooth = juce::ImageCache::getFromMemory(BinaryData::inverse_sawtooth_png, BinaryData::inverse_sawtooth_pngSize);
    inverseSawtoothButton.setImages(
        false,
        true,
        true,
        inverse_sawtooth,
        1.0f,
        juce::Colours::white,
        inverse_sawtooth,
        1.0f,
        juce::Colours::grey,
        inverse_sawtooth,
        1.0f,
        juce::Colours::black
    );
}
