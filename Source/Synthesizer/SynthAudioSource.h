//#include <JuceHeader.h>
//
//
////NOTE cant use this audio source with a plugin.  No go. https://forum.juce.com/t/simple-sampler-example/34674/9
//
//// This is an audio source that streams the output of our demo synth.
//struct SynthAudioSource  : public AudioSource{
//    SynthAudioSource (MidiKeyboardState& keyState)  : keyboardState (keyState){
//        // Add some voices to our synth, to play the sounds..
//        for (auto i = 0; i < 4; ++i){
//            synth.addVoice (new SineWaveVoice());   // These voices will play our custom sine-wave sounds..
//            synth.addVoice (new SamplerVoice());    // and these ones play the sampled sounds
//        }
//
//        // ..and add a sound for them to play...
//        setUsingSineWaveSound();
//    }
//
//    void setUsingSineWaveSound(){
//        synth.clearSounds();
//        synth.addSound (new SineWaveSound());
//    }
//
//    void setUsingSampledSound(){
//        WavAudioFormat wavFormat;
//
//        std::unique_ptr<AudioFormatReader> audioReader (wavFormat.createReaderFor (createAssetInputStream ("cello.wav"), true));
//
//        BigInteger allNotes;
//        allNotes.setRange (0, 128, true);
//
//        synth.clearSounds();
//        synth.addSound (new SamplerSound ("demo sound",
//                                          *audioReader,
//                                          allNotes,
//                                          74,   // root midi note
//                                          0.1,  // attack time
//                                          0.1,  // release time
//                                          10.0  // maximum sample length
//        ));
//    }
//
//    void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) override{
//        midiCollector.reset (sampleRate);
//        synth.setCurrentPlaybackSampleRate (sampleRate);
//    }
//
//    void releaseResources() override {}
//
////    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override{
//    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override{
//        // the synth always adds its output to the audio buffer, so we have to clear it
//        // first..
//        bufferToFill.clearActiveBufferRegion();
//
//        // fill a midi buffer with incoming messages from the midi input.
//        MidiBuffer incomingMidi;
//        midiCollector.removeNextBlockOfMessages (incomingMidi, bufferToFill.numSamples);
//
//        // pass these messages to the keyboard state so that it can update the component
//        // to show on-screen which keys are being pressed on the physical midi keyboard.
//        // This call will also add midi messages to the buffer which were generated by
//        // the mouse-clicking on the on-screen keyboard.
//        keyboardState.processNextMidiBuffer (incomingMidi, 0, bufferToFill.numSamples, true);
//
//        // and now get the synth to process the midi events and generate its output.
//        synth.renderNextBlock (*bufferToFill.buffer, incomingMidi, 0, bufferToFill.numSamples);
//    }
//
//    //==============================================================================
//    // this collects real-time midi messages from the midi input device, and
//    // turns them into blocks that we can process in our audio callback
//    MidiMessageCollector midiCollector;
//
//    // this represents the state of which keys on our on-screen keyboard are held
//    // down. When the mouse is clicked on the keyboard component, this object also
//    // generates midi messages for this, which we can pass on to our synth.
//    MidiKeyboardState& keyboardState;
//
//    // the synth itself!
//    Synthesiser synth;
//};