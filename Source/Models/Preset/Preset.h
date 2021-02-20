#pragma once
#include "./KeySignatureGroup.h"
#include<vector>
using namespace std;

class Preset{
public:
    string id;
    vector<KeySignatureGroup> keySignatureGroups;
    int randomizationMinOctave;
    int randomizationMaxOctave;
};