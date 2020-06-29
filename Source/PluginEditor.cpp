/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "ChordicalAudioProcessor.h"
#include "PluginEditor.h"
#include "./Components/AudioSynthesiserDemo.h"
//==============================================================================
ChordicalAudioProcessorEditor::ChordicalAudioProcessorEditor (ChordicalAudioProcessor& p): AudioProcessorEditor (&p), processor (p){
    std::cout << "hello";
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

//    // these define the parameters of our slider object
//    midiVolume.setSliderStyle (Slider::LinearBarVertical);
//    midiVolume.setRange(0.0, 127.0, 1.0);
//    midiVolume.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
//    midiVolume.setPopupDisplayEnabled (true, false, this);
//    midiVolume.setTextValueSuffix (" Volume");
//    midiVolume.setValue(1.0);
//
//    // this function adds the slider to the editor
//    addAndMakeVisible (&midiVolume);

//    addAndMakeVisible(audioSynthesiserDemo);
    addAndMakeVisible (keyboardComponent);
}

ChordicalAudioProcessorEditor::~ChordicalAudioProcessorEditor()
{
}

//==============================================================================
void ChordicalAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("This is Chordical!", getLocalBounds(), Justification::centred, 1);
}

void ChordicalAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // sets the position and size of the slider with arguments (x, y, width, height)
    midiVolume.setBounds (40, 30, 20, getHeight() - 60);
    keyboardComponent.setBounds (8, 96, getWidth() - 16, 64);
}
