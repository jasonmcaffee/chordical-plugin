#pragma once

#include<vector>
using namespace std;

enum NoteSymbol{
    c = 0,
    cSharp = 1,
    d = 2,
    dSharp = 3,
    e = 4,
    f = 5,
    fSharp = 6,
    g = 7,
    gSharp = 8,
    a = 9,
    aSharp = 10,
    b = 11,
};

vector<string> notes = { "c", "c#", "d", "d#", "e", "f", "f#", "g", "g#", "a", "a#", "b" };

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

inline NoteSymbol stringToNoteSymbol(string note){
    if(note == "c"){ return NoteSymbol::c; }
    if(note == "c#"){ return NoteSymbol::cSharp; }
    if(note == "d"){ return NoteSymbol::d; }
    if(note == "d#"){ return NoteSymbol::dSharp; }
    if(note == "e"){ return NoteSymbol::e; }
    if(note == "f"){ return NoteSymbol::f; }
    if(note == "f#"){ return NoteSymbol::fSharp; }
    if(note == "g"){ return NoteSymbol::g; }
    if(note == "g#"){ return NoteSymbol::gSharp; }
    if(note == "a"){ return NoteSymbol::a; }
    if(note == "a#"){ return NoteSymbol::aSharp; }
    if(note == "b"){ return NoteSymbol::b; }
    return NoteSymbol::c;
}