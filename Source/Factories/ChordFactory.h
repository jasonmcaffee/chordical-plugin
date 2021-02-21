#pragma once
#include "../Models/Chord/Chord.h"
#include "../Services/Util/Util.h"
#include "../Models/Note/NoteSymbol.h"
#include "./PredefinedNoteFactory.h"
#include <JuceHeader.h>
#include <vector>
using namespace juce;
using namespace std;

class ChordFactory{
public:
    static String toJsonString(const Chord& chord){
        auto d = new DynamicObject();

        d->setProperty("id", (String)chord.id);
        d->setProperty("label", (String)chord.label);
        d->setProperty("octave", chord.octave);
        d->setProperty("rootNote", (String)noteSymbolToString(chord.rootNote));
        d->setProperty("type", (String)chord.type);
        d->setProperty("notes", PredefinedNoteFactory::toVarArray(chord.notes));

        return Util::convertDynamicObjectToJsonString(d);
    }

    static String toJsonString(const vector<Chord>& chords){
        var array = toVarArray(chords);
        return JSON::toString(array);
    }

    static var toVarArray(const vector<Chord>& chords){
        var array;
        for(auto & chord : chords){
            array.append(toJsonString(chord));
        }
        return array;
    }

    static Chord fromJSONString(String chordString){
//        String decodedNoteString = Util::urlDecode(chordString.toStdString());
        String decodedChordString = chordString;
        var json;
        if(JSON::parse(decodedChordString, json).wasOk()){
            try{
                string id = json["id"].toString().toStdString();
                string label = json["label"].toString().toStdString();
                int octave = json["octave"];
                NoteSymbol rootNote = stringToNoteSymbol(json["rootNote"].toString().toStdString());
                string type = json["type"].toString().toStdString();

                vector<PredefinedNote> notes = {};
                Array<var>* notesArray = json["notes"].getArray();
                if(notesArray != nullptr){
                    String notesArrayString = JSON::toString(*notesArray);
                    notes = PredefinedNoteFactory::fromJSONStringArray(notesArrayString);
                }

                return Chord {id, label, octave, rootNote, type, notes};

            }catch(exception& e){
                std::cout << "exception while parsing Chord json: " << e.what() << std::endl;
                throw e;
            }
        }
        throw std::invalid_argument("json for Chord could not be parsed");
    }

    static vector<Chord> fromJSONStringArray(String chordsString){
        std::cout << "chordsString: " << chordsString << std::endl;
        vector<Chord> result = {};
        var json;
        if(JSON::parse(chordsString, json).wasOk()){
            try{
                Array<var>* chordsArray = json.getArray();
                for(auto & chord : *chordsArray){
                    auto deserializedChord = fromJSONString(chord.toString());
                    result.push_back(deserializedChord);
                }
            }catch(exception& e){
                std::cout << "error parsing chord in chords string: " << e.what() << std::endl;
                throw e;
            }
            return result;
        }
        throw std::invalid_argument("chordsString could not be parsed");
    }
};


