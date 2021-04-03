#pragma once
#include "../Models/AppState/AppStateHost.h"
#include "../Services/Util/Util.h"
#include <JuceHeader.h>
#include "./PresetFactory.h"
class AppStateFactory{
public:
    static String toJSONString(const AppStateHost& appState){
        auto d = new DynamicObject();
        d->setProperty("preset", PresetFactory::toJSONString(appState.preset));
        return Util::convertDynamicObjectToJsonString(d);
    }

    static AppStateHost fromJSONString(String appStateString){
        var json;
        if(JSON::parse(appStateString, json).wasOk()){
            auto preset = PresetFactory::fromJSONString(json["preset"]);
            return AppStateHost{preset};
        }
        std::cout << "appState string could not be parsed" << std::endl;
        throw std::invalid_argument("appState string could not be parsed");
    }
};