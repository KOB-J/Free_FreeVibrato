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
{
    edge = 5;
    setSize(500, 250);

    addAndMakeVisible(sweepWidthVibratoSlider);
    addAndMakeVisible(waveformsVibratoSlider);
}

FreeVibratoAudioProcessorEditor::~FreeVibratoAudioProcessorEditor()
{
}

//==============================================================================
void FreeVibratoAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::white);

    g.setColour(juce::Colours::dodgerblue);

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
    waveformsVibratoSlider.setBounds(200, 75, 100, 100);

}
