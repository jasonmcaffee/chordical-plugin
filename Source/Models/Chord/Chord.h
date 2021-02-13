#pragma once
#include "../Note/NoteSymbol.h"
#include "../Note/PredefinedNote.h"
#include<string>
#include<vector>
using namespace std;

class Chord{
public:
    string id;
    string label;
    int octave; //useful when we need to regenerate a chord based on type. let's us construct a new chord with settings of previous.
    NoteSymbol rootNote;
    string type; //chord type
    vector<PredefinedNote> notes;
};
