#pragma once

#include "../Services/Util/Util.h"
#include "../Models/Preset/Preset.h"
#include "./KeySignatureGroupFactory.h"
#include <JuceHeader.h>
#include <vector>
using namespace juce;
using namespace std;

class PresetFactory{
public:
    static String toJSONString(const Preset& preset){
        auto d = new DynamicObject();

        d->setProperty("id", (String)preset.id);
        d->setProperty("keySignatureGroups", KeySignatureGroupFactory::toVarArray(preset.keySignatureGroups));

        return Util::convertDynamicObjectToJsonString(d);
    }

    static Preset fromJSONString(String presetString){
        var json;
        if(JSON::parse(presetString, json).wasOk()){
            try{
                string id = json["id"].toString().toStdString();
                vector<KeySignatureGroup> keySignatureGroups = {};
                Array<var>* groupsArray = json["keySignatureGroups"].getArray();
                if(groupsArray != nullptr){
                    String groupsArrayString = JSON::toString(*groupsArray);
                    keySignatureGroups = KeySignatureGroupFactory::fromJSONStringArray(groupsArrayString);
                }
                return Preset {id, keySignatureGroups};
            }catch(exception& e){
                std::cout << "exception parsing preset string: " << e.what() << std::endl;
                throw e;
            }
        }
        std::cout << "preset string could not be parsed" << std::endl;
        throw std::invalid_argument("preset string could not be parsed");
    }
};