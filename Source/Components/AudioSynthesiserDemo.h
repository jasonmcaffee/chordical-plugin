//
//#pragma once
//#include <JuceHeader.h>
//#include "../Utils/DemoUtilities.h"
//#include "../Utils/AudioLiveScrollingDisplay.h"
//#include "../Synthesizer/Sine/SineWaveSound.h"
//#include "../Synthesizer/Sine/SineWaveVoice.h"
//#include "../Synthesizer/SynthAudioSource.h"
//
//class AudioSynthesiserDemo  : public Component{
//public:
//    AudioSynthesiserDemo(){
//        addAndMakeVisible (keyboardComponent);
//
//        addAndMakeVisible (sineButton);
//        sineButton.setRadioGroupId (321);
//        sineButton.setToggleState (true, dontSendNotification);
//        sineButton.onClick = [this] { synthAudioSource.setUsingSineWaveSound(); };
//
//        addAndMakeVisible (sampledButton);
//        sampledButton.setRadioGroupId (321);
//        sampledButton.onClick = [this] { synthAudioSource.setUsingSampledSound(); };
//
//        addAndMakeVisible (liveAudioDisplayComp);
//        audioDeviceManager.addAudioCallback (&liveAudioDisplayComp);
//        audioSourcePlayer.setSource (&synthAudioSource);
//
////#ifndef JUCE_DEMO_RUNNER
//        RuntimePermissions::request (RuntimePermissions::recordAudio,
//                                     [this] (bool granted)
//                                     {
//                                         int numInputChannels = granted ? 2 : 0;
//                                         audioDeviceManager.initialise (numInputChannels, 2, nullptr, true, {}, nullptr);
//                                     });
////#endif
//
//        audioDeviceManager.addAudioCallback (&audioSourcePlayer);
//        audioDeviceManager.addMidiInputDeviceCallback ({}, &(synthAudioSource.midiCollector));
//
//        setOpaque (true);
//        setSize (640, 480);
//    }
//
//    //destructor
//    ~AudioSynthesiserDemo() override{
//        audioSourcePlayer.setSource (nullptr);
//        audioDeviceManager.removeMidiInputDeviceCallback ({}, &(synthAudioSource.midiCollector));
//        audioDeviceManager.removeAudioCallback (&audioSourcePlayer);
//        audioDeviceManager.removeAudioCallback (&liveAudioDisplayComp);
//    }
//
//    //==============================================================================
//    void paint (Graphics& g) override{
//        g.fillAll (getUIColourIfAvailable (LookAndFeel_V4::ColourScheme::UIColour::windowBackground));
//    }
//
//    void resized() override{
//        keyboardComponent   .setBounds (8, 96, getWidth() - 16, 64);
//        sineButton          .setBounds (16, 176, 150, 24);
//        sampledButton       .setBounds (16, 200, 150, 24);
//        liveAudioDisplayComp.setBounds (8, 8, getWidth() - 16, 64);
//    }
//
//private:
//    AudioDeviceManager audioDeviceManager;
//
//    MidiKeyboardState keyboardState;
//    AudioSourcePlayer audioSourcePlayer;
//    SynthAudioSource synthAudioSource        { keyboardState };
//    MidiKeyboardComponent keyboardComponent  { keyboardState, MidiKeyboardComponent::horizontalKeyboard};
//
//    ToggleButton sineButton     { "Use sine wave" };
//    ToggleButton sampledButton  { "Use sampled sound" };
//
//    LiveScrollingAudioDisplay liveAudioDisplayComp;
//
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioSynthesiserDemo)
//};
