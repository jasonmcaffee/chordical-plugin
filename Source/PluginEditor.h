/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ChordicalAudioProcessor.h"
#include "./Components/AudioSynthesiserDemo.h"

//==============================================================================
/**
*/
class ChordicalAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    ChordicalAudioProcessorEditor (ChordicalAudioProcessor&);
    ~ChordicalAudioProcessorEditor();//destructor

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ChordicalAudioProcessor& processor;
    Slider midiVolume; // [1]
    AudioSynthesiserDemo audioSynthesiserDemo;

    MidiKeyboardState keyboardState;
    MidiKeyboardComponent keyboardComponent  { keyboardState, MidiKeyboardComponent::horizontalKeyboard};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChordicalAudioProcessorEditor)
};
