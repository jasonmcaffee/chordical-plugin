#pragma once
#include "../Models/Chord/Chord.h"
#include "../Services/Util/Util.h"
#include "../Models/Note/NoteSymbol.h"
#include <JuceHeader.h>
using namespace juce;

class ChordFactory{
public:
    String toJsonString(const Chord& chord){
        auto d = new DynamicObject();

        d->setProperty("id", (String)chord.id);
        d->setProperty("label", (String)chord.label);
        //        String rootNoteString = noteSymbolToString(chord.rootNote);
        d->setProperty("octave", chord.octave);
        d->setProperty("rootNote", (String)noteSymbolToString(chord.rootNote));
        d->setProperty("type", (String)chord.type);


        return Util::convertDynamicObjectToJsonString(d);
    }
};


