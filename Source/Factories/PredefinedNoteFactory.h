#pragma once

#include "../Models/Chord/Chord.h"
#include "../Models/Note/PredefinedNote.h"
#include "../Services/Util/Util.h"
#include "../Models/Note/NoteSymbol.h"
#include "../Services/Util/Util.h"
#include <JuceHeader.h>
#include <vector>
#include <exception>
using namespace juce;
using namespace std;

class PredefinedNoteFactory{
public:
    static String toJSONString(const PredefinedNote& note){
        auto d = new DynamicObject();

        d->setProperty("id", (String)note.id);
        d->setProperty("noteSymbol", (String)noteSymbolToString(note.noteSymbol));
        d->setProperty("octave", note.octave);
        d->setProperty("midiNoteNumber", note.midiNoteNumber);
        d->setProperty("frequency", note.frequency);

        return Util::convertDynamicObjectToJsonString(d);
    }

    static String toJSONString(const vector<PredefinedNote>& notes){
        String result = "";
        for(auto & note : notes){
            String noteString = toJSONString(note);
            result = result + noteString;
        }
        return result;
    }

    static PredefinedNote fromJSONString(String& noteString){
        String decodedNoteString = Util::urlDecode(noteString.toStdString());
        juce::var json;
        if(juce::JSON::parse(decodedNoteString, json).wasOk()){
            try{
                string id = json["id"].toString().toStdString();
                string noteSymbolString = json["noteSymbol"].toString().toStdString();
                NoteSymbol noteSymbol = stringToNoteSymbol(json["noteSymbol"].toString().toStdString());
                std::cout << "note symbol string: " << noteSymbolString << " noteSymbol: " << noteSymbol << std::endl;
                int octave = json["octave"];
                int midiNoteNumber = json["midiNoteNumber"];
                float frequency = json["frequency"];
                auto note = PredefinedNote {id, noteSymbol, octave, midiNoteNumber, frequency};
                return note;
            }catch(exception& e){
                std::cout << "exception parsing predefined note json: " << e.what() << std::endl;
            }

        }
        throw 20;
//        return nullptr;
    }
};
