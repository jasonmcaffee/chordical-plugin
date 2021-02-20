#pragma once

#include "../Chord/Chord.h"
#include <vector>
using namespace std;

class Slot{
public:
    Chord chord;
    int midiNoteTrigger;
    int qwertyKeyCodeTrigger;

};