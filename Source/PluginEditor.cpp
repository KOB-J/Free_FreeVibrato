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
{
    edge = 5;
    setSize(500, 250);

    addAndMakeVisible(sweepWidthVibratoSlider);
    addAndMakeVisible(lfoFrequencyVibratoSlider);
    addAndMakeVisible(vibratoLabel);
    addAndMakeVisible(undoRedoComponent);
    addAndMakeVisible(vibratoComboBox);
    addAndMakeVisible(waveformsComponent);
    addAndMakeVisible(interpolationComponent);
}

FreeVibratoAudioProcessorEditor::~FreeVibratoAudioProcessorEditor()
{
}

//==============================================================================
void FreeVibratoAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::white);

    g.setColour(pluginBackgroundColor);
    //g.setColour(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

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
    sweepWidthVibratoSlider.setBounds(50, getHeight() * 0.3, 100, 100);
    lfoFrequencyVibratoSlider.setBounds(200, getHeight() * 0.3, 100, 100);

    vibratoLabel.setBounds(edge + 15, edge + 5, getWidth() / 4, getHeight() / 5);

    undoRedoComponent.setSize(100, 30);
    undoRedoComponent.setTopLeftPosition(getWidth() - (getWidth() / 4), edge);

    vibratoComboBox.setBounds(getWidth() * 0.7, getHeight() - (edge + 30), 100, 30);

    waveformsComponent.setSize(200, 100);
    waveformsComponent.setTopLeftPosition(50,  getHeight() - 80);

    interpolationComponent.setSize(100, 100);
    interpolationComponent.setTopLeftPosition(getWidth() * 0.7f, getHeight() * 0.3f);
}
