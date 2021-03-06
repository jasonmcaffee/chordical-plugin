#pragma once
#include <JuceHeader.h>
#include "../Services/EventBus/EventBus.h"

inline juce::String convertDynamicObjectToJsonString(DynamicObject* json){
    juce::var jsonVar(json);
    juce::String jsonString = juce::JSON::toString(jsonVar, true);
    return jsonString;
}

inline juce::String convertAppStateLoadedToJSONString(AppState appState){

    auto dataObj = new DynamicObject();
    juce::String s = appState.state;
    dataObj->setProperty("state", s);

    auto* messageObj = new DynamicObject();
    messageObj->setProperty("type", "appStateLoaded");
    messageObj->setProperty("data", dataObj);

    return convertDynamicObjectToJsonString(messageObj);
}

inline juce::String convertMidiNotePlayedToJSONString(MidiNotePlayedMessage message){

    auto dataObj = new DynamicObject();
    dataObj->setProperty("midiNote", message.data.midiNote);
    dataObj->setProperty("velocity", message.data.velocity);

    auto* messageObj = new DynamicObject();
    messageObj->setProperty("type", "midiNotePlayed");
    messageObj->setProperty("data", dataObj);

    return convertDynamicObjectToJsonString(messageObj);
}

inline juce::String convertMidiNoteStoppedToJSONString(MidiNoteStoppedMessage message){

    auto dataObj = new DynamicObject();
    dataObj->setProperty("midiNote", message.data.midiNote);
    dataObj->setProperty("velocity", message.data.velocity);

    auto* messageObj = new DynamicObject();
    messageObj->setProperty("type", "midiNoteStopped");
    messageObj->setProperty("data", dataObj);

    return convertDynamicObjectToJsonString(messageObj);
}

inline juce::String convertTestMessageToJSONString(TestMessage message){
    auto* messageObj = new DynamicObject();
    messageObj->setProperty("data", static_cast<String &&>(message.data));
    messageObj->setProperty("type", "testMessage");
    return convertDynamicObjectToJsonString(messageObj);
};



inline RequestToPlayMidiNotesMessage convertJSONStringToRequestToPlayMidiNotesMessage(juce::var json){
    std::vector<MidiNoteData> midiNoteDataVector;

    if(auto dataJsonArray = json.getProperty("data", var()).getArray()){
        for(auto& midiNoteDataJson : *dataJsonArray){
            int midiNote = midiNoteDataJson.getProperty("midiNote", int());
            float velocity = midiNoteDataJson.getProperty("velocity", float());
            midiNoteDataVector.push_back(MidiNoteData {midiNote, velocity});
        }
    }
    return RequestToPlayMidiNotesMessage {midiNoteDataVector};
}

inline RequestToChangeWindowSizeMessage convertJSONStringToRequestToChangeWindowSizeMessage(juce::var json){
//    auto json2 = json.getDynamicObject();
//    auto data = json2->getProperty("data");
    auto data = json["data"];
    int windowHeight = data.getProperty("windowHeight", 900);
    int windowWidth = data.getProperty("windowWidth", 900);
    WindowSize windowSize = {windowWidth, windowHeight};
    return RequestToChangeWindowSizeMessage {windowSize};
}

inline RequestToStopMidiNotesMessage convertJSONStringToRequestToStopMidiNotesMessage(juce::var json){
    std::vector<MidiNoteData> midiNoteDataVector;

    if(auto dataJsonArray = json.getProperty("data", var()).getArray()){
        for(auto& midiNoteDataJson : *dataJsonArray){
            int midiNote = midiNoteDataJson.getProperty("midiNote", int());
            float velocity = midiNoteDataJson.getProperty("velocity", float());
            midiNoteDataVector.push_back(MidiNoteData {midiNote, velocity});
        }
    }
    return RequestToStopMidiNotesMessage {midiNoteDataVector};
}

inline RequestToSaveAppStateMessage convertJSONStringToRequestToSaveAppStateMessage(juce::var json){
    juce::String dataAsJuceString = json.getProperty("data", juce::String());
    auto data = dataAsJuceString.toStdString();
    auto appState = AppState { data };
    return RequestToSaveAppStateMessage { appState };
}