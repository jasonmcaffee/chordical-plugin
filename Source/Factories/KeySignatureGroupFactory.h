#pragma once

#include "../Models/Preset/KeySignatureGroup.h"
#include "./KeySignatureFactory.h"
#include "./SlotFactory.h"
#include "../Services/Util/Util.h"
#include <JuceHeader.h>
#include <vector>
using namespace juce;
using namespace std;

class KeySignatureGroupFactory{
public:
    static String toJSONString(const KeySignatureGroup& group){
        auto d = new DynamicObject();

        d->setProperty("id", (String)group.id);
        d->setProperty("keySignature", KeySignatureFactory::toJSONString(group.keySignature));
        d->setProperty("randomizationMaxOctave", group.randomizationMaxOctave);
        d->setProperty("randomizationMinOctave", group.randomizationMinOctave);
        d->setProperty("slots", SlotFactory::toVarArray(group.slots));

        return Util::convertDynamicObjectToJsonString(d);
    }

    static var toVarArray(const vector<KeySignatureGroup>& keySignatureGroups){
        var array;
        for(auto & k : keySignatureGroups){
            String kString = toJSONString(k);
            array.append(kString);
        }
        return array;
    }

    static vector<KeySignatureGroup> fromJSONStringArray(String keySignatureGroupsString){
        vector<KeySignatureGroup> result = {};
        var json;
        if(JSON::parse(keySignatureGroupsString, json).wasOk()){
            try{
                Array<var>* kArray = json.getArray();
                for(auto & k: *kArray){
                    auto deserializedKeySignatureGroup = fromJSONString(k.toString());
                    result.push_back(deserializedKeySignatureGroup);
                }
            }catch(exception& e){
                std::cout << "exception parsing keySignatureGroup array" << std::endl;
            }
            return result;
        }
        std::cout << "keySignatureGroups string could not be parsed" << std::endl;
        throw std::invalid_argument("keySignatureGroups string could not be parsed");
    }

    static KeySignatureGroup fromJSONString(String keySignatureGroupString){
        var json;
        if(JSON::parse(keySignatureGroupString, json).wasOk()){
            try{
                string id = json["id"].toString().toStdString();
                KeySignature keySignature = KeySignatureFactory::fromJSONString(json["keySignature"]);
                int randomizationMinOctave = json["randomizationMinOctave"];
                int randomizationMaxOctave = json["randomizationMaxOctave"];
                vector<Slot> slots = {};
                Array<var>* slotsArray = json["slots"].getArray();
                if(slotsArray != nullptr){
                    slots = SlotFactory::fromJsonStringArray(JSON::toString(*slotsArray));
                }
                auto keySignatureGroup = KeySignatureGroup{ id, slots, keySignature, randomizationMinOctave, randomizationMaxOctave, };
                return keySignatureGroup;
            }catch(exception& e){
                std::cout << "exception parsing keySignatureGroup json: " << e.what() << std::endl;
                throw e;
            }
        }
        throw std::invalid_argument("json for keySignatureGroup could not be parsed");
    }
};