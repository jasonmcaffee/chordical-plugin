#pragma once
#include <functional>
#include <queue>
#include <vector>
#include "./EventMessage.h"


//https://www.codeproject.com/Articles/723656/SW-Message-Bus
//https://seanballais.github.io/blog/implementing-a-simple-message-bus-in-cpp/

//using TypeId = uintptr_t;
//
//template < typename T >
//static TypeId GetTypeId(){
//    static uint32_t placeHolder;
//    return (reinterpret_cast<TypeId>(&placeHolder));
//}

class EventBus{
public:

    EventBus(){}
    ~EventBus(){}

    //https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    static EventBus& eventBus(){
        static EventBus instance;
        return instance;
    }
    EventBus(EventBus const&) = delete;
    void operator=(EventBus const&)  = delete;

    //web app load
    std::vector<std::function<void (WebAppLoadedMessage)>> webAppLoadedCallbacks;
    void subscribeToWebAppLoaded(std::function<void (WebAppLoadedMessage)> callback){ webAppLoadedCallbacks.push_back(callback); }
    void emitWebAppLoaded(WebAppLoadedMessage message){ executeCallbacks(webAppLoadedCallbacks, message); }

    std::vector<std::function<void (MidiNotePlayedMessage)>> midiNotePlayedCallbacks;
    void subscribeToMidiNotePlayed(std::function<void (MidiNotePlayedMessage)> callback){ midiNotePlayedCallbacks.push_back(callback); }
    void emitMidiNotePlayed(MidiNotePlayedMessage message){ executeCallbacks(midiNotePlayedCallbacks, message); }

    std::vector<std::function<void (MidiNoteStoppedMessage)>> midiNoteStoppedCallbacks;
    void subscribeToMidiNoteStopped(std::function<void (MidiNoteStoppedMessage)> callback){ midiNoteStoppedCallbacks.push_back(callback); }
    void emitMidiNoteStopped(MidiNoteStoppedMessage message){ executeCallbacks(midiNoteStoppedCallbacks, message); }

    template <typename TMessageType>
    void executeCallbacks(std::vector< std::function<void (TMessageType)> > callbacks, TMessageType message){
        for(auto & callback : callbacks){
            callback(message);
        }
    }

private:
};


//https://stackoverflow.com/questions/13980157/c-class-with-template-member-variable
//    std::map<TypeId, EventCallbackFuncVector> eventMessageTypeIdToCallbacksMap;


////global singleton https://stackoverflow.com/questions/1463707/c-singleton-vs-global-static-object
//EventBus & eventBus() {
//    static EventBus theEventBus;
//    return theEventBus;
//}

//
//template <typename TMessageType>
//void subscribe2(const std::function<void (EventMessage<TMessageType>)> callback){
//    TypeId typeId = GetTypeId<TMessageType>();
//    auto callbacksIter = eventMessageTypeIdToCallbacksMap.find(typeId);
//    if(callbacksIter == eventMessageTypeIdToCallbacksMap.end()){
//        std::cout  << "no callbacks for type id: " << typeId << std::endl;
//
//        EventCallbackFuncVector callbacks;
////            EventCallbackFunc* castedCallback = static_cast<EventCallbackFunc*>(callback);
////            callbacks.push_back(static_cast<const std::function<void(EventMessageBase)>>(callback));
//        callbacks.push_back(callback);
//
//        EventMessageTypeIdCallbacksPair typeIdCallbacksPair {typeId, callbacks};
//        eventMessageTypeIdToCallbacksMap.insert(typeIdCallbacksPair);
//    }else{
//        std::cout << "callbacks exist" << std::endl;
//        EventCallbackFuncVector callbacks = callbacksIter->second;
//        callbacks.push_back(callback);
//    }
//}
//template <typename TMessageType>
//void emitMessage2(EventMessage<TMessageType> message){
//    TypeId typeId = GetTypeId<TMessageType>();
//    auto callbacksIter = eventMessageTypeIdToCallbacksMap.find(typeId);
//    if(callbacksIter != eventMessageTypeIdToCallbacksMap.end()){
//        EventCallbackFuncVector callbacks = callbacksIter->second;
//        for(auto & callback : callbacks){
//            std::cout << "callback executing!" << std::endl;
//            callback(message);
//        }
//    }else{
//        std::cout << "no listeners for type id: " << typeId << std::endl;
//    }
//}
//
//using EventCallbackFunc = std::function<void (EventMessageBase)>;
//using EventCallbackFuncVector = std::vector<EventCallbackFunc>;
//using EventMessageTypeIdCallbacksPair = std::pair<TypeId, EventCallbackFuncVector>;