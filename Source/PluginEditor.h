/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ChordicalAudioProcessor.h"

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

    MidiKeyboardState keyboardState;
    MidiKeyboardComponent keyboardComponent  { keyboardState, MidiKeyboardComponent::horizontalKeyboard};

    Label versionLabel    { "VersionLabel",  "Version 1" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChordicalAudioProcessorEditor)
};
