#pragma once
#include <functional>
#include <queue>
#include <vector>
#include "./EventMessage.h"


//https://www.codeproject.com/Articles/723656/SW-Message-Bus
//https://seanballais.github.io/blog/implementing-a-simple-message-bus-in-cpp/

using TypeId = uintptr_t;

using EventCallbackFunc = std::function<void(EventMessageBase)>;
using EventCallbackWithMessagePointerFunc = std::function<void(std::shared_ptr<EventMessageBase>)>;


struct EventCallbackContainer{
public:
    int id; //so we can delete from vector later
    EventCallbackWithMessagePointerFunc callback;
};

//using EventCallbackContainerVector = std::vector<EventCallbackContainer>;
//needs to be a shared pointer so we can push_back and have everything have the same values
using EventCallbackContainerVector = std::shared_ptr<std::vector<EventCallbackContainer>>;

using MessageTypeIdToEventCallbackContainerVectorPair = std::pair<TypeId, EventCallbackContainerVector>;

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

    //these are for the plugin to send midi to the browser
    std::vector<std::function<void (MidiNotePlayedMessage)>> midiNotePlayedCallbacks;
    void subscribeToMidiNotePlayed(std::function<void (MidiNotePlayedMessage)> callback){ midiNotePlayedCallbacks.push_back(callback); }
    void emitMidiNotePlayed(MidiNotePlayedMessage message){ executeCallbacks(midiNotePlayedCallbacks, message); }

    std::vector<std::function<void (MidiNoteStoppedMessage)>> midiNoteStoppedCallbacks;
    void subscribeToMidiNoteStopped(std::function<void (MidiNoteStoppedMessage)> callback){ midiNoteStoppedCallbacks.push_back(callback); }
    void emitMidiNoteStopped(MidiNoteStoppedMessage message){ executeCallbacks(midiNoteStoppedCallbacks, message); }

    std::vector<std::function<void (RequestToPlayMidiNotesMessage)>> requestToPlayMidiNotesCallbacks;
    void subscribeToRequestToPlayMidiNotes(std::function<void (RequestToPlayMidiNotesMessage)> callback){ requestToPlayMidiNotesCallbacks.push_back(callback); }
    void emitRequestToPlayMidiNotes(RequestToPlayMidiNotesMessage message){ executeCallbacks(requestToPlayMidiNotesCallbacks, message); }

    std::vector<std::function<void (RequestToStopMidiNotesMessage)>> requestToStopMidiNotesCallbacks;
    void subscribeToRequestToStopMidiNotes(std::function<void (RequestToStopMidiNotesMessage)> callback){ requestToStopMidiNotesCallbacks.push_back(callback); }
    void emitRequestToStopMidiNotes(RequestToStopMidiNotesMessage message){ executeCallbacks(requestToStopMidiNotesCallbacks, message); }


    template <typename TMessageType>
    void subscribe(std::function<void(TMessageType)> callback){
        //create a function that uses shared_ptr message type, so we can downcast
        EventCallbackWithMessagePointerFunc f2 = [callback](std::shared_ptr<EventMessageBase> message){
            //cast the EventMessageBase message as shared_ptr<TMesssageType>
            std::shared_ptr<TMessageType> derived = std::dynamic_pointer_cast<TMessageType>(message);
            //get the value of the the object
            TMessageType derivedValue = *derived.get();
            //execute the callback
            callback(derivedValue);
        };

        auto typeId = GetTypeId<TMessageType>();
        int callbackId = 1; //TODO
        auto callbackContainer = EventCallbackContainer { callbackId, f2 };

        //see if message typeid already has callbacks registered.  if not, create vector and add to map
        auto callbacksContainerVectorIter = messageTypeIdToEventCallbackContainerVector.find(typeId);
        if(callbacksContainerVectorIter == messageTypeIdToEventCallbackContainerVector.end()){
            //message has no callbacks registered, so create new vector
            std::vector<EventCallbackContainer> callbackContainers;
            callbackContainers.push_back(callbackContainer);
            EventCallbackContainerVector callbackContainersSharedPtr = std::make_shared<std::vector<EventCallbackContainer>>(callbackContainers);
            //insert new vector into map
            MessageTypeIdToEventCallbackContainerVectorPair typeIdCallbacksPair {typeId, callbackContainersSharedPtr};
            messageTypeIdToEventCallbackContainerVector.insert(typeIdCallbacksPair);
        }else{
            //message already has callbacks registered, so add to existing vector.
            EventCallbackContainerVector callbackContainers = callbacksContainerVectorIter->second;
            callbackContainers->push_back(callbackContainer);
        }

    }

    template <typename TMessageType>
    void emitMessage(TMessageType message){
        auto typeId = GetTypeId<TMessageType>();
        auto callbacksIter = messageTypeIdToEventCallbackContainerVector.find(typeId);
        if(callbacksIter != messageTypeIdToEventCallbackContainerVector.end()){
            EventCallbackContainerVector callbackContainers = callbacksIter->second;
            for(auto & callbackContainer : *callbackContainers){
                std::shared_ptr<EventMessageBase> mm2 = std::make_shared<TMessageType>(message);
                callbackContainer.callback(mm2);
            }
        }else{
            std::cout << "no listeners for type id: " << typeId << std::endl;
        }
    }

    void test(){

        subscribe<WebAppLoadedMessage>([](WebAppLoadedMessage m){
            std::cout << "WebAppLoadedMessage subscriber called with " << m.data << std::endl;
        });

        subscribe<WebAppLoadedMessage>([](WebAppLoadedMessage m){
            std::cout << "WebAppLoadedMessage subscriber2 called with " << m.data << std::endl;
        });

        subscribe<TestMessage>([](TestMessage m){
            std::cout << "TestMessage subscriber called with " << m.data << std::endl;
        });

        emitMessage(WebAppLoadedMessage{"hello"});
        emitMessage(TestMessage{"test"});
    }

    template <typename TMessageType>
    void executeCallbacks(std::vector< std::function<void (TMessageType)> > callbacks, TMessageType message){
        for(auto & callback : callbacks){
            callback(message);
        }
    }

private:
    std::map<TypeId, EventCallbackContainerVector> messageTypeIdToEventCallbackContainerVector;
};

// playing with pointer funcs
//EventCallbackWithMessagePointerFunc f2 = [](std::shared_ptr<EventMessageBase> message){
//    std::shared_ptr<WebAppLoadedMessage> derived = std::dynamic_pointer_cast<WebAppLoadedMessage>(message);
//    std::cout << "data -----" << derived->data << std::endl;
//};
//
//std::shared_ptr<WebAppLoadedMessage> mmm = std::make_shared<WebAppLoadedMessage>(WebAppLoadedMessage {"hello"}); //https://stackoverflow.com/questions/32050665/can-i-use-stdmake-shared-with-structs-that-dont-have-a-parametric-constructor
//f2(mmm);
//
//auto m = WebAppLoadedMessage {"tacos"};
//std::shared_ptr<EventMessageBase> mm2 = std::make_shared<WebAppLoadedMessage>(m);
//f2(mm2);




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