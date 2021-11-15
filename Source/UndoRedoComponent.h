/*
  ==============================================================================

    UndoRedoComponent.h
    Created: 15 Nov 2021 8:31:22am
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
//#include "PluginProcessor.h"
#include "Constants.h"

class UndoRedoComponent : public juce::Component
{
public:
    UndoRedoComponent(FreeVibratoAudioProcessor& p)
        : audioProcessor(p)
    {
        addAndMakeVisible(undoButton);
        addAndMakeVisible(redoButton);

        undoButton.setButtonText("undo");
        redoButton.setButtonText("redo");

        setColour(juce::GroupComponent::ColourIds::outlineColourId, juce::Colours::black);

        undoButton.setColour(juce::TextButton::buttonColourId, pluginColor);
        redoButton.setColour(juce::TextButton::buttonColourId, pluginColor);

        undoButton.onClick = [this] {audioProcessor.getApvts()->undoManager->undo(); };
        redoButton.onClick = [this] {audioProcessor.getApvts()->undoManager->redo(); };

    }

    ~UndoRedoComponent()
    {

    }

    void resized() override
    {
        undoButton.setBounds(getX(), getY(), getWidth() / 2, getHeight());
        redoButton.setBounds(getWidth() / 2, getY(), getWidth() / 2, getHeight());
    }

private:
    FreeVibratoAudioProcessor& audioProcessor;

    juce::TextButton undoButton, redoButton;
};