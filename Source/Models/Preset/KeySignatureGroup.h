#pragma once
#include "./Slot.h"
#include "../Scale/KeySignature.h"
#include <vector>
#include <string>
using namespace std;

class KeySignatureGroup{
public:
    string id;
    vector<Slot> slots;
    KeySignature keySignature;
};