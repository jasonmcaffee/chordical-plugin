#pragma once

using namespace std;
enum NoteSymbol{
    c,
    cSharp,
    d,
    dSharp,
    e,
    f,
    fSharp,
    g,
    gSharp,
    a,
    aSharp,
    b,
};

inline string noteSymbolToString(NoteSymbol noteSymbol){
    switch(noteSymbol){
        case NoteSymbol::c: { return "c"; }
        case NoteSymbol::cSharp: { return "c#"; }
        case NoteSymbol::d: { return "d"; }
        case NoteSymbol::dSharp: { return "d#"; }
        case NoteSymbol::e: { return "e"; }
        case NoteSymbol::f: { return "f"; }
        case NoteSymbol::fSharp: { return "f#"; }
        case NoteSymbol::g: { return "g"; }
        case NoteSymbol::gSharp: { return "g#"; }
        case NoteSymbol::a: { return "a"; }
        case NoteSymbol::aSharp: { return "a#"; }
        case NoteSymbol::b: { return "b"; }
    }
    return "unknown";
}