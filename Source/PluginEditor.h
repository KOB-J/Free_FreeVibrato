/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "VibratoSlider.h"
#include "VibratoLabel.h"
#include "UndoRedoComponent.h"
#include "VibratoComboBox.h"
#include "Constants.h"
#include "WaveformsComponent.h"
#include "InterpolationComponent.h"
#include "SliderComponent.h"


class FreeVibratoAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FreeVibratoAudioProcessorEditor (FreeVibratoAudioProcessor&);
    ~FreeVibratoAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    int edge;

    FreeVibratoAudioProcessor& audioProcessor;

    //TODO use unique_ptr
    VibratoSlider sweepWidthVibratoSlider, lfoFrequencyVibratoSlider;
    VibratoLabel vibratoLabel;
    UndoRedoComponent undoRedoComponent;
    VibratoComboBox vibratoComboBox; 
    WaveformsComponent waveformsComponent;
    InterpolationComponent interpolationComponent;
    SliderComponent sliderComponent;

    juce::AudioProcessorValueTreeState::SliderAttachment sweepWidthSliderAttachment, lfoFrenquencySliderAttachment;

    void configureSliderLabelValues();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FreeVibratoAudioProcessorEditor)
};
