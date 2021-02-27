#pragma once

#include "../Models/Preset/KeySignatureGroup.h"
#include "../Services/Util/Util.h"
#include <JuceHeader.h>
#include <vector>
using namespace juce;
using namespace std;

class KeySignatureGroupFactory{
public:
    static String toJSONString(const KeySignatureGroup& group){
        auto d = new DynamicObject();



        return Util::convertDynamicObjectToJsonString(d);
    }
};