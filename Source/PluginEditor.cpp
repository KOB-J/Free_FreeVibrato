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
{
    edge = 5;
    setSize(500, 250);

    addAndMakeVisible(sweepWidthVibratoSlider);
    addAndMakeVisible(lfoFrequencyVibratoSlider);
    addAndMakeVisible(vibratoLabel);
    addAndMakeVisible(undoRedoComponent);
    addAndMakeVisible(vibratoComboBox);
}

FreeVibratoAudioProcessorEditor::~FreeVibratoAudioProcessorEditor()
{
}

//==============================================================================
void FreeVibratoAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::white);

    g.setColour(pluginColor);

    juce::Path roundedBackground;
    juce::Rectangle<int> localBounds = getLocalBounds();
    localBounds.reduce(edge, edge);
    roundedBackground.addRoundedRectangle(localBounds, 20.0f);
    g.fillPath(roundedBackground);
}

void FreeVibratoAudioProcessorEditor::resized()
{
    auto bounds = getBounds();

    //TODO set responsive sizes
    sweepWidthVibratoSlider.setBounds(50, 75, 100, 100);
    lfoFrequencyVibratoSlider.setBounds(200, 75, 100, 100);

    vibratoLabel.setBounds(edge + 15, edge + 5, getWidth() / 4, getHeight() / 5);

    undoRedoComponent.setSize(100, 30);
    undoRedoComponent.setTopLeftPosition(getWidth() - (getWidth() / 4), edge);

    vibratoComboBox.setBounds(getWidth() - (getWidth() / 2), edge, 100, 30);
}
