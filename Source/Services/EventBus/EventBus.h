#pragma once
#include <functional>
#include <queue>
#include <vector>
#include "./EventMessage.h"

//https://www.codeproject.com/Articles/723656/SW-Message-Bus
using TypeId = uintptr_t;

template < typename T >
static TypeId GetTypeId(){
    static uint32_t placeHolder;
    return (reinterpret_cast<TypeId>(&placeHolder));
}

class MsgTypeContainerBase{
public:
    MsgTypeContainerBase() = default;
    virtual ~MsgTypeContainerBase() = default;
    MsgTypeContainerBase( MsgTypeContainerBase& ) = delete;
    MsgTypeContainerBase( MsgTypeContainerBase&& ) = delete;
    MsgTypeContainerBase& operator= ( MsgTypeContainerBase& ) = delete;
    MsgTypeContainerBase& operator= ( MsgTypeContainerBase&& ) = delete;
//    virtual void Remove( SubscriberHandle handle ) = 0;
    virtual bool Empty() = 0;
};

template <typename TMessageType>
class MsgTypeContainer : public MsgTypeContainerBase{
public:
    void Add(){

    }
private:
//    using MsgBusContainerMap = std::map<

};


class EventBus{
public:
    EventBus(){}
    ~EventBus(){}

    //https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    static EventBus& getInstance(){
        static EventBus instance;
        return instance;
    }
    EventBus(EventBus const&) = delete;
    void operator=(EventBus const&)  = delete;

    void subscribe(std::function<void (EventMessageBase)> callback){
        callbacks.push_back(callback);
    }

    void emitMessage(EventMessageBase message){
        for(auto callbacksIterator = callbacks.begin(); callbacksIterator != callbacks.end(); callbacksIterator++){
            auto callback = (*callbacksIterator);
            callback(message);
        }
    }

    template <typename TMessageType>
    void subscribe2(EventMessage<TMessageType> message){
        TypeId typeId = GetTypeId<TMessageType>();

    }

private:
    std::vector<std::function<void (EventMessageBase)>> callbacks;

//    template <typename TMessageType>
//    using EventMessageCallback = std::function<void (TMessageType)>;
//
//    using EventMessageTypeToCallbacksMap = std::map<TypeId, std::function<void (TMessageType)>
//    template <typename TMessageType>
//    std::map<TypeId, std::function<void (TMessageType)>> eventMessageTypeToCallbacksMap;

};

////global singleton https://stackoverflow.com/questions/1463707/c-singleton-vs-global-static-object
//EventBus & eventBus() {
//    static EventBus theEventBus;
//    return theEventBus;
//}