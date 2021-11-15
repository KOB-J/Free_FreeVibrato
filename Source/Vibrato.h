/*
  ==============================================================================

    Vibrato.h
    Created: 15 Nov 2021 6:23:30am
    Author:  dev

  ==============================================================================
*/

#pragma once


#define _USE_MATH_DEFINES
#include <JuceHeader.h>
#include <math.h>

const float kMaximumSweepWidth = 0.05;

class Vibrato
{
public:

    Vibrato();

    ~Vibrato();

    void prepare(double sampleRate, int samplesPerBlock);

    void process(
        juce::AudioBuffer<float>& buffer,
        float& sweepWidth,
        float& lfoFrequency,
        float& Waveforms,
        float& Interpolation);

    void reset();

    enum Waveforms
    {
        kWaveformSine = 1,
        kWaveformTriangle,
        kWaveformSquare,
        kWaveformSawtooth,
        kWaveformInverseSawtooth,
        kNumWaveforms
    };

    enum Interpolation
    {
        kInterpolationNearestNeighbour = 1,
        kInterpolationLinear,
        kInterpolationCubic,
        kNumInterpolations
    };


private:

    double vibratoSampleRate;
    int vibratoSamplesPerBlock;

    float lfo(float phase, int waveform);

    juce::AudioSampleBuffer delayBuffer;
    int delayBufferLength;
    int delayWritePosition;

    float lfoPhase;
    double inverseSampleRate;

    float sweepWidth;
    float frequency;
    int   waveform;
    int   interpolation;
};
