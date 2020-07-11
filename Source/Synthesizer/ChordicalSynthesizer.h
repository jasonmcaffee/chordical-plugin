
#define JUCE_CORE_INCLUDE_NATIVE_HEADERS 1

struct midiData {
    int noteNumber;
    int velocity;
};
struct midiDataResult {
    std::vector<midiData> onNotes;
    std::vector<midiData> offNotes;
};

// Short-term solution: use the inline keyword for functions defined in header files https://stackoverflow.com/questions/51795364/duplicate-symbol-for-struct-in-header-guarded-file
// Long term: Don't have any code inlined unless it's a measurable performance degradation. (Code in header files is forbidden on my team). Have your header files as follows:
inline midiDataResult getMidiData(MidiBuffer& midiMessages){
    std::vector<midiData> onNotes;
    std::vector<midiData> offNotes;
    if(midiMessages.isEmpty()){ return {onNotes, offNotes}; }
    MidiMessage message (0xf4, 0.0);
    MidiBuffer::Iterator i (midiMessages);
    int messageFrameRelativeToThisProcess;
    while(i.getNextEvent(message, messageFrameRelativeToThisProcess)){
        if(message.isNoteOn(true)){
            auto noteNumber = message.getNoteNumber();
            auto velocity = message.getVelocity();
            midiData onNote = { noteNumber, velocity };
            onNotes.push_back(onNote);
        }else if(message.isNoteOff(true)){
            auto noteNumber = message.getNoteNumber();
            midiData offNote = {noteNumber};
            offNotes.push_back(offNote);
        }
    }
    midiDataResult result = { onNotes, offNotes };
    return result;
}

class ChordicalSynthesizer{
public:
    ChordicalSynthesizer(){}

    void prepareToPlay (double sampleRate, int samplesPerBlock) {
        this->sampleRate = sampleRate;
        this->samplesPerBlock = samplesPerBlock;
    }

    void processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages){
        auto midiData = getMidiData(midiMessages);
        if(midiData.onNotes.size() > 0){
            std::cout << "onNotes size: " << midiData.onNotes.size() << std::endl;
        }
        if(midiData.offNotes.size() > 0){
            std::cout << "offNotes size: " << midiData.offNotes.size() << std::endl;
        }
    }

    void startNote(int midi){

    }
private:
    double sampleRate;
    int samplesPerBlock;
};



