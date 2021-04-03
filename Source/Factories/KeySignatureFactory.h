#pragma once
#include "../Models/Scale/KeySignature.h"
#include "../Services/Util/Util.h"
#include "../Models/Note/NoteSymbol.h"
#include "../Models/Scale/ScaleType.h"
#include <JuceHeader.h>
#include <vector>
#include <exception>
//#include <cereal/archives/json.hpp>
using namespace juce;
using namespace std;

class KeySignatureFactory{
public:
    static String toJSONString(const KeySignature& key){
        auto d = new DynamicObject();

        d->setProperty("rootNote", (String)noteSymbolToString(key.rootNote));
        d->setProperty("scale", (String)scaleTypeToString(key.scale));

        return Util::convertDynamicObjectToJsonString(d);
    }

    static KeySignature fromJSONString(String keySignatureString){
        var json;
        if(JSON::parse(keySignatureString, json).wasOk()){
            try{
                NoteSymbol rootNote = stringToNoteSymbol(json["rootNote"].toString().toStdString());
                ScaleType scale = stringToScaleType(json["scale"].toString().toStdString());
                auto keySignature = KeySignature{ rootNote, scale};
                return keySignature;
            }catch(exception& e){
                std::cout << "exception parsing keySignatureString: " << e.what() << std::endl;
                throw e;
            }
        }
        throw std::invalid_argument("json for keySignature could not be parsed");
    }

//    static String toJSONStringV2(const KeySignature& key){
//        std::stringstream ss;
//        {
//            cereal::JSONOutputArchive oarchive(ss);
//            oarchive(key);
//        }
//        return ss.str();
//    }

};