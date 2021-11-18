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
        auto black = juce::Colour::fromFloatRGBA(0.08f, 0.08f, 0.08f, 1.0f);
        auto blue = juce::Colour::fromFloatRGBA(0.43f, 0.83f, 1.0f, 1.0f);
        auto darkBlue = juce::Colour::fromFloatRGBA(0.1f, 0.f, 0.7f, 1.0f);
        auto blueAlpha = juce::Colour::fromFloatRGBA(0.43f, 0.83f, 1.0f, 0.2f);
        auto darkBlueAlpha = juce::Colour::fromFloatRGBA(0.1f, 0.f, 0.7f, 0.2f);
        //g.fillAll(black);

        auto bounds = juce::Rectangle<float>(x, y, width, height).withSizeKeepingCentre(width, height);

        juce::Path circle1;
        circle1.addEllipse(bounds);
        //g.setColour(juce::Colours::white);

        g.setGradientFill(juce::ColourGradient(
            juce::Colours::white,//juce::Colours::orange,
            x,
            y,
            juce::Colours::grey,//juce::Colours::magenta,
            width,
            height,
            false
        ));

        g.fillPath(circle1);

        juce::Path path3;

        //path3.addPieSegment(bounds,
        //    0,// -2 * juce::MathConstants<float>::pi / 3,
        //    //11 * juce::MathConstants<float>::pi / 6 * slider.getValue(),
        //    juce::MathConstants<float>::twoPi * slider.getValue() * (1 / slider.getMaximum()),
        //    0.2f);

        ////path2.applyTransform(juce::AffineTransform::rotation(juce::MathConstants<float>::pi));

        //g.setGradientFill(juce::ColourGradient(
        //    blueAlpha,//juce::Colours::orange,
        //    x,
        //    y,
        //    darkBlueAlpha,//juce::Colours::magenta,
        //    width,
        //    height,
        //    false
        //));
        ////g.setColour(juce::Colours::orange);
        //g.fillPath(path3);


        //***********************************

        juce::Path path2;
        bounds.reduce(3, 3);
        path2.addPieSegment(bounds,
            0,// -2 * juce::MathConstants<float>::pi / 3,
            //11 * juce::MathConstants<float>::pi / 6 * slider.getValue(),
            juce::MathConstants<float>::twoPi,// *slider.getValue() * (1 / slider.getMaximum()),
            0.7f);

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

        bounds.reduce(7, 7);
        juce::Path circle2;
        circle2.addEllipse(bounds);
        g.setColour(pluginColor);
        g.fillPath(circle2);

        ////*****************************

        juce::Path inner;
        bounds.reduce(3, 3);
        inner.addPieSegment(bounds,
            0,// -2 * juce::MathConstants<float>::pi / 3,
            //11 * juce::MathConstants<float>::pi / 6 * slider.getValue(),
            juce::MathConstants<float>::twoPi * slider.getValue() * (1 / slider.getMaximum()),
            0.95f);

        //path2.applyTransform(juce::AffineTransform::rotation(juce::MathConstants<float>::pi));
        g.setColour(juce::Colours::white);


        //g.setGradientFill(juce::ColourGradient(
        //    blue,//juce::Colours::orange,
        //    x,
        //    y,
        //    darkBlue,//juce::Colours::magenta,
        //    width,
        //    height,
        //    false
        //));
        //g.setColour(juce::Colours::orange);
        g.fillPath(inner);

        ////*****************************

        //juce::Path path;
        //path.addPieSegment(bounds,
        //    0,//juce::MathConstants<float>::twoPi,
        //    juce::MathConstants<float>::twoPi,
        //    0.5f);

        //g.setColour(blue);
        //g.strokePath(path, juce::PathStrokeType(1.5f));

        auto centreX = width / 2;
        auto centreY = height / 2;
        auto halfCentreX = centreX / 2;
        auto halfCentreY = centreY / 2;
        auto centreXMinus = (width / 2) - 15;
        auto centreYMinus = (height / 2) - 15;

        auto theta = slider.getValue() * (1 / slider.getMaximum()) * juce::MathConstants<float>::twoPi;
        theta -= juce::MathConstants<float>::halfPi;
        DBG("theta: " << theta);
        //auto line = juce::Line<float>((centreX * cos(theta)) + centreX, (centreY * sin(theta)) + centreY, centreX, centreY);
        auto line = juce::Line<float>((centreXMinus * cos(theta)) + centreX, (centreYMinus * sin(theta)) + centreY, (halfCentreX * cos(theta)) + centreX, (halfCentreY * sin(theta)) + centreY);

        g.drawLine(line);

        //line.addLineSegment(juce::Line<float>(centreX, centreY, centreX, y + 13), 2.0f);

        //juce::Path line;

        //auto point1 = juce::Point<float>(width, height);// centreX, y + 13);
        //auto point2 = juce::Point<float>(centreX, centreY);


        //point1.applyTransform(juce::AffineTransform().rotation(juce::MathConstants<float>::twoPi* slider.getValue()* (1 / slider.getMaximum())));

        //line.addLineSegment(juce::Line<float>(point1, point2), 2.0f);

        //g.fillPath(line);
    }

private:

};
