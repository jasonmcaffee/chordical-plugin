#pragma once
#include "./NoteSymbol.h"
#include<string>
using namespace std;

class PredefinedNote{
public:
    string id; //c0
    NoteSymbol noteSymbol; //cSharp
    int octave;//0
    int midiNoteNumber;//21
    float frequency;//.9887878
};