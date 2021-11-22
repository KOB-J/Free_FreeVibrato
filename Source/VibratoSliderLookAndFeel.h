/*
  ==============================================================================

    VibratoSliderLookAndFeel.h
    Created: 15 Nov 2021 6:24:38am
    Author:  dev

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Constants.h"

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
        auto bounds = juce::Rectangle<float>(x, y, width, height).withSizeKeepingCentre(width, height);

        juce::Path circle1;
        circle1.addEllipse(bounds);

        g.setGradientFill(juce::ColourGradient(
            juce::Colours::white,
            x,
            y,
            juce::Colours::grey,
            width,
            height,
            false
        ));

        g.fillPath(circle1);

        //*****
        juce::Path inner1;
        //bounds.reduce(3, 3);
        inner1.addPieSegment(bounds,
            0,
            juce::MathConstants<float>::twoPi * slider.getValue() * (1 / slider.getMaximum()),
            0.5f);

        g.setColour(sliderProgressCurve);//juce::Colours::white);

        g.fillPath(inner1);
        //*****

        juce::Path path3;

        juce::Path path2;
        bounds.reduce(3, 3);
        path2.addPieSegment(bounds,
            0,
            juce::MathConstants<float>::twoPi,
            0.7f);

        g.setGradientFill(juce::ColourGradient(
            blue,
            x,
            y,
            darkBlue,
            width,
            height,
            false
        ));

        g.fillPath(path2);

        bounds.reduce(7, 7);
        juce::Path circle2;
        circle2.addEllipse(bounds);
        g.setColour(sliderTopColor);
        g.fillPath(circle2);


        juce::Path inner;
        bounds.reduce(3, 3);
        inner.addPieSegment(bounds,
            0,
            juce::MathConstants<float>::twoPi * slider.getValue() * (1 / slider.getMaximum()),
            0.95f);

        g.setColour(juce::Colours::black);

        g.fillPath(inner);

        g.setColour(juce::Colours::white);

        auto centreX = width / 2;
        auto centreY = height / 2;
        auto halfCentreX = centreX / 2;
        auto halfCentreY = centreY / 2;
        auto centreXMinus = (width / 2) - 15;
        auto centreYMinus = (height / 2) - 15;

        auto theta = slider.getValue() * (1 / slider.getMaximum()) * juce::MathConstants<float>::twoPi;
        theta -= juce::MathConstants<float>::halfPi;
        //DBG("theta: " << theta);
        auto line = juce::Line<float>((centreXMinus * cos(theta)) + centreX, (centreYMinus * sin(theta)) + centreY, (halfCentreX * cos(theta)) + centreX, (halfCentreY * sin(theta)) + centreY);

        g.drawLine(line);
    }

private:

};
