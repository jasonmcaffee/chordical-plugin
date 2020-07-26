/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Services/EventBus/EventBus.h"


//==============================================================================
ChordicalAudioProcessorEditor::ChordicalAudioProcessorEditor (PluginProcessor& p): AudioProcessorEditor (&p), processor (p){
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (700, 600);

//    addAndMakeVisible (keyboardComponent);
//    addAndMakeVisible (versionLabel);

    addAndMakeVisible(webBrowserComponent);
    webBrowserComponent.setBounds(0, 0, getWidth(), getHeight());

    EventBus::getInstance().emitMessage(EventMessageBase("work"));

}

ChordicalAudioProcessorEditor::~ChordicalAudioProcessorEditor(){}

//==============================================================================
void ChordicalAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("3.0", getLocalBounds(), Justification::centred, 1);
}

void ChordicalAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // sets the position and size of the slider with arguments (x, y, width, height)
    midiVolume.setBounds (40, 30, 20, getHeight() - 60);
    keyboardComponent.setBounds (8, 96, getWidth() - 16, 64);
}
