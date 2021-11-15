/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FreeVibratoAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FreeVibratoAudioProcessorEditor (FreeVibratoAudioProcessor&);
    ~FreeVibratoAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    int edge;

    FreeVibratoAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreeVibratoAudioProcessorEditor)
};
