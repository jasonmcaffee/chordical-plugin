#pragma once

using TypeId = uintptr_t;
template < typename T >
static TypeId GetTypeId(){
    static uint32_t placeHolder;
    return (reinterpret_cast<TypeId>(&placeHolder));
}

//needed so we can store functions that accept EventMessage types.
struct EventMessageBase {
    public:
        EventMessageBase(){}
        // dynamic_pointer_cast needs one virtual function; https://stackoverflow.com/questions/5831765/c-is-not-a-polymorphic-type-while-using-boostdynamic-pointer-cast
        //you need to implement the virtual function with {} or you get missing vtable error https://stackoverflow.com/questions/15265106/c-a-missing-vtable-error
        virtual ~EventMessageBase(){};
    };

template <typename TMessageData>
struct EventMessage : public EventMessageBase{
public:
    TypeId typeId;
    TMessageData data;
    EventMessage(TMessageData dataParam){
        TypeId typeId2 = GetTypeId<TMessageData>();
        data = dataParam;
    }
};

//shorthand for calling parent constructor is to use using EventMessage::EventMessage
struct WebAppLoadedMessage : public EventMessage<std::string>{ public: using EventMessage::EventMessage; };
struct TestMessage : public EventMessage<std::string>{ public: using EventMessage::EventMessage; };

struct MidiNoteData { int midiNote; float velocity; };
struct MidiNotePlayedMessage : public EventMessage<MidiNoteData> { using EventMessage::EventMessage; };
struct MidiNoteStoppedMessage : public EventMessage<MidiNoteData> { using EventMessage::EventMessage; };

struct RequestToPlayMidiNotesMessage : public EventMessage<std::vector<MidiNoteData>> { using EventMessage::EventMessage; };
struct RequestToStopMidiNotesMessage : public EventMessage<std::vector<MidiNoteData>> { using EventMessage::EventMessage; };


