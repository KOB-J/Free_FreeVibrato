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
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
