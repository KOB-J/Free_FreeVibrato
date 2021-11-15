/*
  ==============================================================================

    VibratoSliderLookAndFeel.h
    Created: 15 Nov 2021 6:24:38am
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class VibratoSliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    VibratoSliderLookAndFeel() {}
    ~VibratoSliderLookAndFeel() {}

    virtual void drawRotarySlider(juce::Graphics& g,
        int x, int y, int width, int height,
        float sliderPosProportional,
        float rotaryStartAngle,
        float rotaryEndAngle,
        juce::Slider& slider) override
    {
        auto black = juce::Colour::fromFloatRGBA(0.08f, 0.08f, 0.08f, 1.0f);
        auto blue = juce::Colour::fromFloatRGBA(0.43f, 0.83f, 1.0f, 1.0f);
        auto darkBlue = juce::Colour::fromFloatRGBA(0.1f, 0.f, 0.7f, 1.0f);
        auto blueAlpha = juce::Colour::fromFloatRGBA(0.43f, 0.83f, 1.0f, 0.2f);
        auto darkBlueAlpha = juce::Colour::fromFloatRGBA(0.1f, 0.f, 0.7f, 0.2f);
        //g.fillAll(black);

        auto bounds = juce::Rectangle<float>(x, y, width, height).withSizeKeepingCentre(width, height);

        juce::Path path3;

        path3.addPieSegment(bounds,
            0,// -2 * juce::MathConstants<float>::pi / 3,
            //11 * juce::MathConstants<float>::pi / 6 * slider.getValue(),
            juce::MathConstants<float>::twoPi * slider.getValue() * (1 / slider.getMaximum()),
            0.2f);

        //path2.applyTransform(juce::AffineTransform::rotation(juce::MathConstants<float>::pi));

        g.setGradientFill(juce::ColourGradient(
            blueAlpha,//juce::Colours::orange,
            x,
            y,
            darkBlueAlpha,//juce::Colours::magenta,
            width,
            height,
            false
        ));
        //g.setColour(juce::Colours::orange);
        g.fillPath(path3);


        //***********************************

        juce::Path path2;

        path2.addPieSegment(bounds,
            0,// -2 * juce::MathConstants<float>::pi / 3,
            //11 * juce::MathConstants<float>::pi / 6 * slider.getValue(),
            juce::MathConstants<float>::twoPi * slider.getValue() * (1 / slider.getMaximum()),
            0.5f);

        //path2.applyTransform(juce::AffineTransform::rotation(juce::MathConstants<float>::pi));


        g.setGradientFill(juce::ColourGradient(
            blue,//juce::Colours::orange,
            x,
            y,
            darkBlue,//juce::Colours::magenta,
            width,
            height,
            false
        ));
        //g.setColour(juce::Colours::orange);
        g.fillPath(path2);

        //*****************************


        juce::Path path;
        path.addPieSegment(bounds,
            0,//juce::MathConstants<float>::twoPi,
            juce::MathConstants<float>::twoPi,
            0.5f);

        g.setColour(blue);
        g.strokePath(path, juce::PathStrokeType(1.5f));
    }

private:

};
