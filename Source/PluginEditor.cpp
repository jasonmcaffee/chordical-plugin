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


    addAndMakeVisible(webBrowserComponent);
    webBrowserComponent.setBounds(0, 0, getWidth(), getHeight());

//    addAndMakeVisible (versionLabel);

//    EventBus::eventBus().emitWebAppLoaded(WebAppLoadedMessage {"asdf"});
//    EventBus::eventBus().emitMidiNotePlayed(MidiNotePlayedMessage { MidiNoteData { 44, 100 }});

}

ChordicalAudioProcessorEditor::~ChordicalAudioProcessorEditor(){}

//==============================================================================
void ChordicalAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::yellow);
    g.setFont (24.0f);
    g.drawFittedText ( File::getCurrentWorkingDirectory().getFullPathName(), getLocalBounds(), Justification::centred, 3);
}

void ChordicalAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // sets the position and size of the slider with arguments (x, y, width, height)
    midiVolume.setBounds (40, 30, 20, getHeight() - 60);
    keyboardComponent.setBounds (8, 96, getWidth() - 16, 64);
}
