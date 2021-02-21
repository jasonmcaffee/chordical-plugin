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
        var array;
        for(auto & chord: chords){
            auto chordString = toJsonString(chord);
            array.append(chordString);
        }
        return JSON::toString(array);
    }

    static Chord fromJSONString(String chordString){
//        String decodedNoteString = Util::urlDecode(chordString.toStdString());
        String decodedNoteString = chordString;
        std::cout << "chord string: " << decodedNoteString << std::endl;
        var json;
        if(JSON::parse(decodedNoteString, json).wasOk()){
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
                    std::cout << "notesArrayString : " << notesArrayString << std::endl;
                    notes = PredefinedNoteFactory::fromJSONStringArray(notesArrayString);
                }

                return Chord {id, label, octave, rootNote, type, notes};

            }catch(exception& e){
                std::cout << "exception while parsing Chord json: " << e.what() << std::endl;
                throw e;
            }
        }
        throw std::invalid_argument("json for PredefinedNote could not be parsed");
    }
};


