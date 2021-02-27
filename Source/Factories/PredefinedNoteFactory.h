#pragma once

#include "../Models/Chord/Chord.h"
#include "../Models/Note/PredefinedNote.h"
#include "../Services/Util/Util.h"
#include "../Models/Note/NoteSymbol.h"
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
        var array = toVarArray(notes);
        return JSON::toString(array);
    }

    static var toVarArray(const vector<PredefinedNote>& notes){
        var array;
        for(auto & note : notes){
            String noteString = toJSONString(note);
            array.append(noteString);
        }
        return array;
    }

    static PredefinedNote fromJSONString(String noteString){
//        String decodedNoteString = Util::urlDecode(noteString.toStdString());
        String decodedNoteString = noteString;
        var json;
        if(JSON::parse(decodedNoteString, json).wasOk()){
            try{
                string id = json["id"].toString().toStdString();
                string noteSymbolString = json["noteSymbol"].toString().toStdString();
                NoteSymbol noteSymbol = stringToNoteSymbol(json["noteSymbol"].toString().toStdString());
                int octave = json["octave"];
                int midiNoteNumber = json["midiNoteNumber"];
                float frequency = json["frequency"];
                auto note = PredefinedNote {id, noteSymbol, octave, midiNoteNumber, frequency};
                return note;
            }catch(exception& e){
                std::cout << "exception parsing predefined note json: " << e.what() << std::endl;
                throw e;
            }
        }
        throw std::invalid_argument("json for PredefinedNote could not be parsed");
    }

    static vector<PredefinedNote> fromJSONStringArray(String notesString){
        vector<PredefinedNote> result = {};
//        String decodedNoteString = Util::urlDecode(notesString.toStdString());
        String decodedNoteString = notesString;
        var json;
        if(JSON::parse(decodedNoteString, json).wasOk()){
            try{
                Array<var>* notesArray = json.getArray();
                for(auto & note: *notesArray){
                    auto deserializedNote = fromJSONString(note.toString());
                    result.push_back(deserializedNote);
                }
            }catch(exception& e){
                std::cout << "exception parsing predefined note array: " << e.what() << std::endl;
                throw e;
            }
            return result;

        }
        std::cout << "notes string could not be parsed" << std::endl;
        throw std::invalid_argument("notes string could not be parsed");
    }
};
