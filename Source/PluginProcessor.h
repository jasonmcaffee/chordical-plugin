/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Synthesizer/ChordicalSynthesizer.h"
#include "Services/Synthesizer/ChordicalOscillator/ChordicalJuceSynth.h"
#include "Services/EventBus/EventMessage.h"
#include "Services/AutoChorder/AutoChorder.h"

using AudioGraphIOProcessor = juce::AudioProcessorGraph::AudioGraphIOProcessor;
using Node = juce::AudioProcessorGraph::Node;

//==============================================================================
/**
*/
class PluginProcessor  : public AudioProcessor, private Timer
{
public:
    //==============================================================================
    PluginProcessor();
    ~PluginProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void timerCallback() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void initializeGraph();
    void updateGraph();
    void connectAudioNodes();
    void connectMidiNodes();

private:
    //==============================================================================
    Synthesiser synth; //<-- original osc voice player. may go away once graph is implemented.

    ChordicalSynthesizer synthesizer;

    ChordicalJuceSynth chordicalJuceSynth;

    std::queue<MidiNoteData> requestToPlayMidiNoteDataQueue;
    std::queue<MidiNoteData> requestToStopMidiNoteDataQueue;

    std::queue<MidiNoteData> sendPlayMidiNoteDataQueue;
    std::queue<MidiNoteData> sendStopMidiNoteDataQueue;

    //audio processor graph & nodes
    std::unique_ptr<juce::AudioProcessorGraph> mainProcessor;
    Node::Ptr audioInputNode;
    Node::Ptr audioOutputNode;
    Node::Ptr midiInputNode;
    Node::Ptr midiOutputNode;

    std::string appState;
    AutoChorder autoChorder;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};
