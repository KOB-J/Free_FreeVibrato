/*
  ==============================================================================

    Constants.h
    Created: 15 Nov 2021 10:37:06am
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


//******* COLOUR ********
static const juce::Colour black = juce::Colour::fromFloatRGBA(0.08f, 0.08f, 0.08f, 1.0f);
static const juce::Colour white = juce::Colour::fromFloatRGBA(1.0f, 1.0f, 1.0f, 1.0f);
static const juce::Colour blue = juce::Colour::fromFloatRGBA(0.43f, 0.83f, 1.0f, 1.0f);
static const juce::Colour darkBlue = juce::Colour::fromFloatRGBA(0.1f, 0.0f, 0.7f, 1.0f);
static const juce::Colour blueAlpha = juce::Colour::fromFloatRGBA(0.43f, 0.83f, 1.0f, 0.2f);
static const juce::Colour darkBlueAlpha = juce::Colour::fromFloatRGBA(0.1f, 0.0f, 0.7f, 0.2f);
static const juce::Colour yellow = juce::Colour::fromFloatRGBA(0.1f, 0.0f, 0.7f, 0.2f);
static const juce::Colour darkYellow = juce::Colour::fromFloatRGBA(0.9f, 0.9f, 0.2f, 1.0f);

static const juce::Colour pluginColor = juce::Colours::dodgerblue;
static const juce::Colour pluginBackgroundColor = juce::Colours::darkslategrey;
static const juce::Colour sliderTopColor = pluginColor;
static const juce::Colour buttonHighlightedColor = yellow;
static const juce::Colour titleColor = darkYellow;
static const juce::Colour sliderProgressCurve = darkYellow;


//******* TEXT ********
static const juce::String sineToolTip = "sine";
static const juce::String triangleToolTip = "triangle";
static const juce::String squareToolTip = "square";
static const juce::String sawtoothToolTip = "sawtooth";
static const juce::String inverseSawtoothToolTip = "inverse sawtooth";

