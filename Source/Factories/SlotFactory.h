#pragma once

#include "../Models/Preset/Slot.h"
#include "../Services/Util/Util.h"
#include "./ChordFactory.h"
#include <JuceHeader.h>
#include <vector>
#include <exception>
using namespace juce;
using namespace std;

class SlotFactory{
public:
    static String toJSONString(const Slot& slot){
        auto d = new DynamicObject();

        d->setProperty("chord", ChordFactory::toJsonString(slot.chord));
        d->setProperty("midiNoteTrigger", slot.midiNoteTrigger);
        d->setProperty("qwertyKeyCodeTrigger", slot.qwertyKeyCodeTrigger);

        return Util::convertDynamicObjectToJsonString(d);
    }

    static var toVarArray(const vector<Slot>& slots){
        var array;
        for(auto & slot : slots){
            String slotString = toJSONString(slot);
            array.append(slotString);
        }
        return array;
    }

    static String toJSONString(vector<Slot>& slots){
        var array = toVarArray(slots);
        return JSON::toString(array);
    }

    static vector<Slot> fromJsonStringArray(String slotsString){
        vector<Slot> result = {};
        String decodedSlotsString = slotsString;
        var json;
        if(JSON::parse(decodedSlotsString, json).wasOk()){
            try{
                Array<var>* slotsArray = json.getArray();
                for(auto & slot : *slotsArray){
                    auto deserializedSlot = fromJSONString(slot);
                    result.push_back(deserializedSlot);
                }
            }catch(exception& e){
                std::cout << "exception parsing slots string array: " << e.what() << std::endl;
                throw e;
            }
            return result;
        }
        throw std::invalid_argument("slots string could not be parsed");
    }

    static Slot fromJSONString(String slotString){
        String decodedSlotString = slotString;
        var json;
        if(JSON::parse(decodedSlotString, json).wasOk()){
            try{
                auto chord = ChordFactory::fromJSONString(json["chord"]);
                int midiNoteTrigger = json["midiNoteTrigger"];
                int qwertyKeyCodeTrigger = json["qwertyKeyCodeTrigger"];
                auto slot = Slot{chord, midiNoteTrigger, qwertyKeyCodeTrigger};
                return slot;
            }catch(exception& e){
                std::cout << "exception parsing slot json: " << e.what() << std::endl;
                throw e;
            }
        }
        throw std::invalid_argument("json for Slot could not be parsed");
    }
};