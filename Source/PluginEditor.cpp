/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


void writeHtmlFileFromBinaryDataToDisk(){
    //https://forum.juce.com/t/example-for-creating-a-file-and-doing-something-with-it/31998/2

    MemoryInputStream memInputStream (ChordicalBinaryData::test_html, ChordicalBinaryData::test_htmlSize,false);
    File f ("/Users/jason/dev/chordical-plugin/test.html");
    f.deleteFile();
    std::cout << "current working dir" << File::getCurrentWorkingDirectory().getFullPathName() << std::endl;
    FileOutputStream stream(f);
    stream.writeFromInputStream(memInputStream, memInputStream.getTotalLength());
    stream.flush();
}

//==============================================================================
ChordicalAudioProcessorEditor::ChordicalAudioProcessorEditor (PluginProcessor& p): AudioProcessorEditor (&p), processor (p){
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (700, 600);

//    addAndMakeVisible (keyboardComponent);
//    addAndMakeVisible (versionLabel);

    writeHtmlFileFromBinaryDataToDisk();

    addAndMakeVisible(webBrowserComponent);
    webBrowserComponent.setBounds(0, 0, getWidth(), getHeight());
//    webBrowserComponent.goToURL("http://127.0.0.1:3001");
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
