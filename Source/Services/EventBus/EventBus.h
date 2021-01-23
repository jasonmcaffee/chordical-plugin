#pragma once
#include <functional>
#include <queue>
#include <vector>
#include "./EventMessage.h"


//https://www.codeproject.com/Articles/723656/SW-Message-Bus
//https://seanballais.github.io/blog/implementing-a-simple-message-bus-in-cpp/

//using TypeId = uintptr_t;

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

//using MessageTypeIdToEventCallbackContainerVectorPair = std::pair<TypeId, EventCallbackContainerVector>;
using MessageTypeIdToEventCallbackContainerVectorPair = std::pair<const char*, EventCallbackContainerVector>;

class EventBus{
public:
    EventBus(){}
    ~EventBus(){}

    std::map<const char*, EventCallbackContainerVector> messageTypeIdToEventCallbackContainerVector;

    //https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    static EventBus& eventBus(){
        static EventBus instance;
        return instance;
    }

    EventBus(EventBus const&) = delete;
    void operator=(EventBus const&)  = delete;

    template <typename TMessageType>
    int subscribe(std::function<void(TMessageType)> callback){

        //create a function that uses shared_ptr message type, so we can downcast
        EventCallbackWithMessagePointerFunc f2 = [callback](std::shared_ptr<EventMessageBase> message){
            //cast the EventMessageBase message as shared_ptr<TMesssageType>
            std::shared_ptr<TMessageType> derived = std::dynamic_pointer_cast<TMessageType>(message);
            //get the value of the the object
            TMessageType derivedValue = *derived.get();
            //execute the callback
            callback(derivedValue);
        };

        const char* typeName = typeid(TMessageType).name();
        std::cout << "message type id name: " << typeName << std::endl;

//        int callbackId = 1; //TODO
        callbackId++;
        auto callbackContainer = EventCallbackContainer { callbackId, f2 };

        //see if message typeid already has callbacks registered.  if not, create vector and add to map
        auto callbacksContainerVectorIter = messageTypeIdToEventCallbackContainerVector.find(typeName);
        if(callbacksContainerVectorIter == messageTypeIdToEventCallbackContainerVector.end()){
            std::cout << "subscribe called for type id with no existing callbacks " << typeName << std::endl;
            //message has no callbacks registered, so create new vector
            std::vector<EventCallbackContainer> callbackContainers;
            callbackContainers.push_back(callbackContainer);
            EventCallbackContainerVector callbackContainersSharedPtr = std::make_shared<std::vector<EventCallbackContainer>>(callbackContainers);
            //insert new vector into map
            MessageTypeIdToEventCallbackContainerVectorPair typeIdCallbacksPair {typeName, callbackContainersSharedPtr};
            messageTypeIdToEventCallbackContainerVector.insert(typeIdCallbacksPair);
        }else{
            std::cout << "subscribe called for type id HAS existing callbacks " << typeName << std::endl;
            //message already has callbacks registered, so add to existing vector.
            EventCallbackContainerVector callbackContainers = callbacksContainerVectorIter->second;
            callbackContainers->push_back(callbackContainer);
        }

        return callbackId;
    }

    void unsubscribe(int callbackId){
        //key is the type name, val is the callback vector
        for (auto const& [key, val] : messageTypeIdToEventCallbackContainerVector){
            EventCallbackContainerVector callbackContainers = val;
            int i = 0;
            int indexToDelete = -1;
            for(auto & callbackContainer: *callbackContainers){
                if(callbackContainer.id == callbackId){
                    indexToDelete = i;
                    break;
                }
                i++;
            }

            if(indexToDelete > -1){
                callbackContainers->erase(callbackContainers->begin() + indexToDelete);
                break;
            }

        }
    }

    template <typename TMessageType>
    void emitMessage(TMessageType message){
        const char *typeName = typeid(TMessageType).name();
        std::cout << "emit type id name: " << typeName << std::endl;

        auto callbacksIter = messageTypeIdToEventCallbackContainerVector.find(typeName);
        if(callbacksIter != messageTypeIdToEventCallbackContainerVector.end()){
            EventCallbackContainerVector callbackContainers = callbacksIter->second;
            for(auto & callbackContainer : *callbackContainers){
                std::shared_ptr<EventMessageBase> mm2 = std::make_shared<TMessageType>(message);
                callbackContainer.callback(mm2);
            }
        }else{
            std::cout << "no callbacks for type id: " << typeName << std::endl;
        }
    }

    void test(){
    }

    template <typename TMessageType>
    void executeCallbacks(std::vector< std::function<void (TMessageType)> > callbacks, TMessageType message){
        for(auto & callback : callbacks){
            callback(message);
        }
    }

private:
    int callbackId = 0;
};
