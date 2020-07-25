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
    }
private:
    // manager object that finds an appropriate way to decode various audio files.  Used with SampleSound objects.
    AudioFormatManager audioFormatManager;
};