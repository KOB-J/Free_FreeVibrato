/*
  ==============================================================================

    UndoRedoComponent.h
    Created: 15 Nov 2021 8:31:22am
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Constants.h"
#include "PluginProcessor.h"


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

        undoButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        undoButton.setColour(juce::TextButton::textColourOffId, pluginColor);

        redoButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        redoButton.setColour(juce::TextButton::textColourOffId, pluginColor);

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