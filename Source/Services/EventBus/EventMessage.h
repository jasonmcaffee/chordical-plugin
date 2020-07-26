#pragma once

class EventMessage{
public:
    EventMessage(const std::string event){
        messageEvent = event;
    }

    std::string getEvent()
    {
        return messageEvent;
    }
private:
    std::string messageEvent;
};