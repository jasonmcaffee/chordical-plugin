#pragma once
#include <functional>
#include <queue>
#include <vector>
#include "./EventMessage.h"

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

    void subscribe(std::function<void (EventMessage)> callback){
        callbacks.push_back(callback);
    }

    void emitMessage(EventMessage message){
        for(auto callbacksIterator = callbacks.begin(); callbacksIterator != callbacks.end(); callbacksIterator++){
            auto callback = (*callbacksIterator);
            callback(message);
        }
    }

private:
    std::vector<std::function<void (EventMessage)>> callbacks;

};

////global singleton https://stackoverflow.com/questions/1463707/c-singleton-vs-global-static-object
//EventBus & eventBus() {
//    static EventBus theEventBus;
//    return theEventBus;
//}