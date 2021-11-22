/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FreeVibratoAudioProcessorEditor::FreeVibratoAudioProcessorEditor (FreeVibratoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
    , sweepWidthSliderAttachment (*p.getApvts(), "sweepWidth", sweepWidthVibratoSlider)
    , lfoFrenquencySliderAttachment (*p.getApvts(), "lfoFrequency", lfoFrequencyVibratoSlider)
    , undoRedoComponent (p)
    , interpolationComponent(p)
    , waveformsComponent(p)
    , vibratoComboBox(p)
    , sliderComponent(p)
{
    edge = 5;
    setSize(500, 250);

    addAndMakeVisible(sliderComponent);
    addAndMakeVisible(sweepWidthVibratoSlider);
    addAndMakeVisible(lfoFrequencyVibratoSlider);
    addAndMakeVisible(vibratoLabel);
    addAndMakeVisible(undoRedoComponent);
    addAndMakeVisible(vibratoComboBox);
    addAndMakeVisible(waveformsComponent);
    addAndMakeVisible(interpolationComponent);

    configureSliderLabelValues();

    vibratoLabel.setColour(juce::Label::textColourId, darkYellow);
}

FreeVibratoAudioProcessorEditor::~FreeVibratoAudioProcessorEditor()
{
}

//==============================================================================
void FreeVibratoAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(pluginBackgroundColor);

    juce::Path roundedBackground;
    juce::Rectangle<int> localBounds = getLocalBounds();
    localBounds.reduce(edge, edge);
    roundedBackground.addRoundedRectangle(localBounds, 20.0f);
    g.fillPath(roundedBackground);

    g.setColour(black);
    g.fillRoundedRectangle(getWidth() * 0.7f, getHeight() * 0.3f, 100.0f, 100.0f, 10.0f);
    g.fillRoundedRectangle(getWidth() * 0.7f, getHeight() * 0.3f, getWidth() * 0.3f, 20.0f, 10.0f);
}

void FreeVibratoAudioProcessorEditor::resized()
{
    auto bounds = getBounds();

    //TODO set responsive sizes

    sliderComponent.setSize(300, 130);
    sliderComponent.setTopLeftPosition(edge, (getHeight() * 0.3) - 30);

    sweepWidthVibratoSlider.setBounds(50, getHeight() * 0.3, 100, 100);
    lfoFrequencyVibratoSlider.setBounds(200, getHeight() * 0.3, 100, 100);

    vibratoLabel.setBounds(edge + 15, edge, getWidth() / 4, getHeight() / 5);

    undoRedoComponent.setSize(100, 20);
    undoRedoComponent.setTopLeftPosition(getWidth() - (getWidth() / 4), edge);

    vibratoComboBox.setBounds(getWidth() * 0.7, getHeight() - (edge + 30), 100, 25);

    waveformsComponent.setSize(200, 100);
    waveformsComponent.setTopLeftPosition(50,  getHeight() - 80);

    interpolationComponent.setSize(100, 100);
    interpolationComponent.setTopLeftPosition(getWidth() * 0.7f, getHeight() * 0.3f);
}

void FreeVibratoAudioProcessorEditor::configureSliderLabelValues()
{
    sliderComponent.getSweepWidthValue()->setText(
        juce::String(sweepWidthVibratoSlider.getValue() * 1000) + " Ms"
        , juce::dontSendNotification);

    sliderComponent.getLfoFrequencyValue()->setText(
        juce::String(lfoFrequencyVibratoSlider.getValue()) + " Hz"
        , juce::dontSendNotification);

    sweepWidthVibratoSlider.onValueChange = [this]
    {
        sliderComponent.getSweepWidthValue()->setText(
            juce::String(sweepWidthVibratoSlider.getValue() * 1000) + " Ms"
            , juce::dontSendNotification);
    };

    lfoFrequencyVibratoSlider.onValueChange = [this]
    {
        sliderComponent.getLfoFrequencyValue()->setText(
            juce::String(lfoFrequencyVibratoSlider.getValue()) + " Hz"
            , juce::dontSendNotification);
    };
}
