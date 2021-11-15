/*
  ==============================================================================

    Vibrato.cpp
    Created: 15 Nov 2021 6:23:30am
    Author:  dev

  ==============================================================================
*/

#include "Vibrato.h"

Vibrato::Vibrato() : delayBuffer(2, 1)
{
    sweepWidth = .01;
    frequency = 2.0;
    waveform = kWaveformSine;
    interpolation = kInterpolationCubic;

    delayBufferLength = 1;
    lfoPhase = 0.0;
    inverseSampleRate = 1.0 / 44100.0;

    delayWritePosition = 0;

    vibratoSampleRate = 0;
    vibratoSamplesPerBlock = 0;
}

Vibrato::~Vibrato()
{
}

void Vibrato::prepare(double sampleRate, int samplesPerBlock)
{
    vibratoSampleRate = sampleRate;
    vibratoSamplesPerBlock = samplesPerBlock;

    delayBufferLength = (int)(kMaximumSweepWidth * sampleRate) + 3;
    delayBuffer.setSize(2, delayBufferLength);
    delayBuffer.clear();
    lfoPhase = 0.0;

    inverseSampleRate = 1.0 / sampleRate;
}

void Vibrato::process(juce::AudioBuffer<float>& buffer, float& sweepWidthParameter, float& lfoFrequencyParameter, float& WaveformsParameter, float& InterpolationParameter)
{
    jassert(vibratoSampleRate != 0);
    jassert(vibratoSamplesPerBlock != 0);

    sweepWidth = sweepWidthParameter;
    frequency = lfoFrequencyParameter;
    waveform = WaveformsParameter;
    interpolation = InterpolationParameter;

    const int numberOfChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    int channel, dpw;
    float dpr, currentDelay, ph;

    for (channel = 0; channel < numberOfChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);

        float* delayData = delayBuffer.getWritePointer(juce::jmin(channel, delayBuffer.getNumChannels() - 1));

        dpw = delayWritePosition;
        ph = lfoPhase;

        for (int i = 0; i < numSamples; ++i)
        {
            const float in = channelData[i];
            float interpolatedSample = 0.0;

            currentDelay = sweepWidth * lfo(ph, waveform);

            dpr = fmodf((float)dpw - (float)(currentDelay * vibratoSampleRate) + (float)delayBufferLength - 3.0,
                (float)delayBufferLength);

            if (interpolation == kInterpolationLinear)
            {
                float fraction = dpr - floorf(dpr);
                int previousSample = (int)floorf(dpr);
                int nextSample = (previousSample + 1) % delayBufferLength;
                interpolatedSample = fraction * delayData[nextSample]
                    + (1.0f - fraction) * delayData[previousSample];
            }
            else if (interpolation == kInterpolationCubic)
            {
                int sample1 = (int)floorf(dpr);
                int sample2 = (sample1 + 1) % delayBufferLength;
                int sample3 = (sample2 + 1) % delayBufferLength;
                int sample0 = (sample1 - 1 + delayBufferLength) % delayBufferLength;

                float fraction = dpr - floorf(dpr);
                float frsq = fraction * fraction;

                float a0 = -0.5f * delayData[sample0] + 1.5f * delayData[sample1]
                    - 1.5f * delayData[sample2] + 0.5f * delayData[sample3];
                float a1 = delayData[sample0] - 2.5f * delayData[sample1]
                    + 2.0f * delayData[sample2] - 0.5f * delayData[sample3];
                float a2 = -0.5f * delayData[sample0] + 0.5f * delayData[sample2];
                float a3 = delayData[sample1];

                interpolatedSample = a0 * fraction * frsq + a1 * frsq + a2 * fraction + a3;
            }
            else
            {
                int closestSample = (int)floorf(dpr + 0.5);
                if (closestSample == delayBufferLength)
                    closestSample = 0;
                interpolatedSample = delayData[closestSample];
            }

            delayData[dpw] = in;

            if (++dpw >= delayBufferLength)
                dpw = 0;

            channelData[i] = interpolatedSample;

            ph += frequency * inverseSampleRate;
            if (ph >= 1.0)
                ph -= 1.0;
        }
    }

    delayWritePosition = dpw;
    lfoPhase = ph;
}

void Vibrato::reset()
{
    delayBuffer.clear();
}

float Vibrato::lfo(float phase, int waveform)
{
    switch (waveform)
    {
    case kWaveformTriangle:
        if (phase < 0.25f)
            return 0.5f + 2.0f * phase;
        else if (phase < 0.75f)
            return 1.0f - 2.0f * (phase - 0.25f);
        else
            return 2.0f * (phase - 0.75f);
    case kWaveformSquare:
        if (phase < 0.5f)
            return 1.0f;
        else
            return 0.0f;
    case kWaveformSawtooth:
        if (phase < 0.5f)
            return 0.5f + phase;
        else
            return phase - 0.5f;
    case kWaveformInverseSawtooth:
        if (phase < 0.5f)
            return 0.5f - phase;
        else
            return 1.5f - phase;
    case kWaveformSine:
    default:
        return 0.5f + 0.5f * sinf(2.0 * M_PI * phase);
    }
}