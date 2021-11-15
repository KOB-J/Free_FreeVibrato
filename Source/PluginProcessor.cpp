/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FreeVibratoAudioProcessor::FreeVibratoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
    , apvts(*this, &undoManager, "parameter", getParameterLayout())
#endif
{
}

FreeVibratoAudioProcessor::~FreeVibratoAudioProcessor()
{
}

//==============================================================================
const juce::String FreeVibratoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FreeVibratoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FreeVibratoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FreeVibratoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FreeVibratoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FreeVibratoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FreeVibratoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FreeVibratoAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FreeVibratoAudioProcessor::getProgramName (int index)
{
    return {};
}

void FreeVibratoAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FreeVibratoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    vibrato.prepare(sampleRate, samplesPerBlock);
}

void FreeVibratoAudioProcessor::releaseResources()
{
    vibrato.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FreeVibratoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FreeVibratoAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    float sweepWidth_ = apvts.getRawParameterValue("sweepWidth")->load();
    float frequency_ = apvts.getRawParameterValue("lfoFrequency")->load();
    float waveform_ = apvts.getRawParameterValue("Waveforms")->load();
    float interpolation_ = apvts.getRawParameterValue("Interpolation")->load();

    vibrato.process(buffer, sweepWidth_, frequency_, waveform_, interpolation_);
}

//==============================================================================
bool FreeVibratoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FreeVibratoAudioProcessor::createEditor()
{
    return new FreeVibratoAudioProcessorEditor (*this);
}

//==============================================================================
void FreeVibratoAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void FreeVibratoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessorValueTreeState::ParameterLayout FreeVibratoAudioProcessor::getParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "sweepWidth",
        "sweepWidth",
        juce::NormalisableRange<float>(0.0f, 0.04f, 0.0005f),
        0.0015f));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        "lfoFrequency",
        "lfoFrequency",
        0.0f,
        10.0f,
        2.0f));

    juce::StringArray waveformsStringArray = { "kWaveformSine" ,
        "kWaveformTriangle",
        "kWaveformSquare",
        "kWaveformSawtooth",
        "kWaveformInverseSawtooth" };


    layout.add(std::make_unique<juce::AudioParameterChoice>(
        "Waveforms",
        "Waveforms",
        waveformsStringArray,
        0));

    juce::StringArray interpolationStringArray = {
        "kInterpolationNearestNeighbour",
        "kInterpolationLinear",
        "kInterpolationCubic" };


    layout.add(std::make_unique<juce::AudioParameterChoice>(
        "Interpolation",
        "Interpolation",
        interpolationStringArray,
        0));

    return layout;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FreeVibratoAudioProcessor();
}
