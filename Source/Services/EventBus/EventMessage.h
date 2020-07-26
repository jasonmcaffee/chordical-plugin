#pragma once


class EventMessageBase{
public:
    std::string type;

    EventMessageBase(const std::string typeParam){
        type = typeParam;
    }

    std::string getType(){
        return type;
    }
};

template <typename TMessageData>
class EventMessage :  EventMessageBase{
public:
    TMessageData data;

    //constructor
    EventMessage(const std::string typeParam, const TMessageData dataParam)
    : EventMessageBase(typeParam){
        data = dataParam;
    }

private:
};