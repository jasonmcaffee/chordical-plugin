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

    setResizable(true, true);
    setSize (700, 600);

    addAndMakeVisible(webBrowserComponent);
    webBrowserComponent.setBounds(0, 0, getWidth(), getHeight());

    //web browser component cant listen to event due to lack of unregister callback on event bus.
    toWebAppEventBusCallbackId = EventBus::eventBus().subscribe<ToWebAppMessage>([this](ToWebAppMessage message){
        std::cout << "start send message to web app" << std::endl;
        webBrowserComponent.sendMessageToWebApp(message.data);
    });

    requestToChangeWindowSizeEventBusCallbackId = EventBus::eventBus().subscribe<RequestToChangeWindowSizeMessage>([this](RequestToChangeWindowSizeMessage message){
       std::cout << "web app loaded height" << message.data.windowHeight << " width: " << message.data.windowWidth << std::endl;
        setSize (message.data.windowWidth , message.data.windowHeight);
    });

}

//destroy is called when the window is minimized in Ableton
ChordicalAudioProcessorEditor::~ChordicalAudioProcessorEditor(){
    EventBus::eventBus().unsubscribe(toWebAppEventBusCallbackId);  //if we don't unsubscribe, the DAW will crash
    EventBus::eventBus().unsubscribe(requestToChangeWindowSizeEventBusCallbackId);  //if we don't unsubscribe, the DAW will crash
}

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
    webBrowserComponent.setBounds(0, 0, getWidth(), getHeight());
}
