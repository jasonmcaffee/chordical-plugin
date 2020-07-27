#pragma once

using TypeId = uintptr_t;
template < typename T >
static TypeId GetTypeId(){
    static uint32_t placeHolder;
    return (reinterpret_cast<TypeId>(&placeHolder));
}

template <typename TMessageData>
struct EventMessage{
    TypeId typeId;
    TMessageData data;
    EventMessage(TMessageData dataParam){
        TypeId typeId2 = GetTypeId<TMessageData>();
        data = dataParam;
    }
};

//shorthand for calling parent constructor is to use using EventMessage::EventMessage
struct WebAppLoadedMessage : public EventMessage<std::string>{ using EventMessage::EventMessage; };

struct MidiNoteData { int midiNote; float velocity; };
struct MidiNotePlayedMessage : public EventMessage<MidiNoteData> { using EventMessage::EventMessage; };
struct MidiNoteStoppedMessage : public EventMessage<MidiNoteData> { using EventMessage::EventMessage; };

struct RequestToPlayMidiNotesMessage : public EventMessage<std::vector<MidiNoteData>> { using EventMessage::EventMessage; };
struct RequestToStopMidiNotesMessage : public EventMessage<std::vector<MidiNoteData>> { using EventMessage::EventMessage; };





//long way of calling parent constructor.
//struct WebAppLoadedMessage : public EventMessage<std::string>{
//    WebAppLoadedMessage(std::string type, std::string data): EventMessage<std::string>(type, data) {}
//};









//struct WebAppLoadedMessage {
//    std::string type;
//    std::string data;
//};



//
//class EventMessageBase{
//public:
//    std::string type;
//
//    EventMessageBase(const std::string typeParam){
//        type = typeParam;
//    }
//
//    virtual ~EventMessageBase() {}
//
//    std::string getType(){
//        return type;
//    }
//
//    template<class T> const T& getData() const; //to be implimented after Parameter
//    template<class T, class U> void setData(const U& rhs); //to be implimented after Parameter
//};
//
//template <typename TMessageData>
//class EventMessage :  EventMessageBase{
//public:
//    TMessageData data;
//
//    //constructor
//    EventMessage(const std::string typeParam, const TMessageData dataParam)
//    : EventMessageBase(typeParam){
//        setData(dataParam);
//    }
//
//    void setData(TMessageData dataParam){
//        data = dataParam;
//    }
//
//    TMessageData getData(){
//        return data;
//    }
//
//private:
//};


