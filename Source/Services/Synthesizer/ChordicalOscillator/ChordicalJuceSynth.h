#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#define MAX_VOICES 16
class ChordicalJuceSynth : public Synthesiser {
public:
    void setup(){
        for (int i = 0; i < MAX_VOICES; i++){
            addVoice(new SamplerVoice());
        }
        //use wav and aiff files
        audioFormatManager.registerBasicFormats();

//        File* file = new File("");
        WavAudioFormat wavFormat;
        std::unique_ptr<AudioFormatReader> audioReaderC4(wavFormat.createReaderFor(new MemoryInputStream(ChordicalBinaryData::c4_wav, ChordicalBinaryData::c4_wavSize,false),true));

        //create the notes that c4 applies to
        BigInteger allNotes;
        allNotes.setRange(0, 128, true);

        auto c4sound = new SamplerSound("C4 piano", *audioReaderC4, allNotes, 60, 0.0, 0.1, 5.0);
        addSound(c4sound);

    }
private:
    // manager object that finds an appropriate way to decode various audio files.  Used with SampleSound objects.
    AudioFormatManager audioFormatManager;
};