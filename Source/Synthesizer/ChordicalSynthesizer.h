
//TODO: Evaluate Maximillian sound c++ library for wave generation https://www.youtube.com/watch?v=Gsd7ESq827c (12:30)

#include "../Processors/GainProcessor.h"
#include "../Processors/OscillatorProcessor.h"
#include "../Processors/FilterProcessor.h"

#pragma once
using AudioGraphIOProcessor = juce::AudioProcessorGraph::AudioGraphIOProcessor;
using Node = juce::AudioProcessorGraph::Node;

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


inline float convertMidiNoteNumberToFrequency(int midiNoteNumber){
    auto a = 440.0;
//    auto freq = (a / 32) * pow(2, ((midiNoteNumber - 9) / 12) );
//    float freq =  a * pow (2.0, (midiNoteNumber - 69) / 12);
    double freq = juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    std::cout << " midiNoteNumber: " << midiNoteNumber << " frequency: " << freq << std::endl;


    return freq;
}

inline std::unique_ptr<juce::AudioProcessorGraph> createGraph(double sampleRate, int blockSize, int mainBusNumInputChannels, int mainBusNumOutputChannels, int midiNoteNumber){

    std::cout << "createGraph called" << std::endl;

    std::unique_ptr<juce::AudioProcessorGraph> mainProcessor = std::make_unique<juce::AudioProcessorGraph>();
    Node::Ptr audioInputNode;
    Node::Ptr audioOutputNode;
    Node::Ptr midiInputNode;
    Node::Ptr midiOutputNode;

    //delete all nodes and connections
//    mainProcessor->clear();

    //create an audio graph processor
    mainProcessor->setPlayConfigDetails(mainBusNumInputChannels, mainBusNumOutputChannels, sampleRate, blockSize);
    mainProcessor->prepareToPlay(sampleRate, blockSize);

    //https://stackoverflow.com/questions/37514509/advantages-of-using-stdmake-unique-over-new-operator
    audioInputNode  = mainProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::audioInputNode));
    audioOutputNode = mainProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::audioOutputNode));
    midiInputNode   = mainProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::midiInputNode));
    midiOutputNode  = mainProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::midiOutputNode));

    auto frequency = convertMidiNoteNumberToFrequency(midiNoteNumber);
    std::cout << "frequency: " << frequency << std::endl;
    //create some nodes/processors to add to our main processor.
    auto gainNode = mainProcessor->addNode(std::make_unique<GainProcessor>());
    auto oscillatorNode = mainProcessor->addNode(std::make_unique<OscillatorProcessor>(frequency));
    auto filterNode = mainProcessor->addNode(std::make_unique<FilterProcessor>());

    //set the play configuration for each node
    gainNode->getProcessor()->setPlayConfigDetails(mainBusNumInputChannels, mainBusNumOutputChannels, sampleRate, blockSize);
    oscillatorNode->getProcessor()->setPlayConfigDetails(mainBusNumInputChannels, mainBusNumOutputChannels, sampleRate, blockSize);
    filterNode->getProcessor()->setPlayConfigDetails(mainBusNumInputChannels, mainBusNumOutputChannels, sampleRate, blockSize);

    //connect the nodes together. add a connection for each of the 2 channels.
    for(int channel = 0; channel < 2; ++channel){
        mainProcessor->addConnection({ {audioInputNode->nodeID, channel}, {oscillatorNode->nodeID, channel}});
        mainProcessor->addConnection({ {oscillatorNode->nodeID, channel}, {gainNode->nodeID, channel} });
        mainProcessor->addConnection({ {gainNode->nodeID, channel}, {filterNode->nodeID, channel} });
        mainProcessor->addConnection({ {filterNode->nodeID, channel}, {audioOutputNode->nodeID, channel} });
    }

    //connect the midi nodes
    mainProcessor->addConnection({ {midiInputNode->nodeID, juce::AudioProcessorGraph::midiChannelIndex}, {midiOutputNode->nodeID, juce::AudioProcessorGraph::midiChannelIndex} });

    //enable buses on all nodes
    for(auto node : mainProcessor->getNodes()){
        node->getProcessor()->enableAllBuses();
    }

    return mainProcessor;
}


class ChordicalSynthesizer{
public:
    ChordicalSynthesizer(){}

    void prepareToPlay (double sampleRate, int samplesPerBlock, int mainBusNumInputChannels, int mainBusNumOutputChannels) {
        this->sampleRate = sampleRate;
        this->samplesPerBlock = samplesPerBlock;
        this->mainBusNumInputChannels = mainBusNumInputChannels;
        this->mainBusNumOutputChannels = mainBusNumOutputChannels;
    }

    void processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages){
        auto midiData = getMidiData(midiMessages);
        for(const auto& offNote : midiData.offNotes){
            std::cout << "offNote noteNumber: " << offNote.noteNumber << std::endl;
            releaseNote(offNote.noteNumber);
        }

        for(const auto& onNote : midiData.onNotes){
            std::cout << "onNote noteNumber: " << onNote.noteNumber << std::endl;
            startNote(onNote.noteNumber);
        }

        //iterate over map and call processBlock on each graph
        for (auto const& x : midiNoteToProcessorGraphHash){
            auto& graph = x.second;
            if(graph){
                graph->processBlock(buffer, midiMessages);
            }
        }

    }

    void startNote(int midiNoteNumber){
//        auto graphForMidiNote = midiNoteToProcessorGraphHash.find(midiNoteNumber);
        auto& graphForMidiNote = midiNoteToProcessorGraphHash[midiNoteNumber];
        if(graphForMidiNote){
            graphForMidiNote->suspendProcessing(true);
            graphForMidiNote->clear();
            graphForMidiNote->releaseResources();
            std::cout << "destroyed existing graph for note: " << midiNoteNumber << std::endl;;
        }

        midiNoteToProcessorGraphHash[midiNoteNumber] = createGraph(sampleRate, samplesPerBlock, mainBusNumInputChannels, mainBusNumOutputChannels, midiNoteNumber);
    }

    void releaseNote(int midiNoteNumber){
        auto& graphForMidiNote = midiNoteToProcessorGraphHash[midiNoteNumber];
        if(graphForMidiNote){
            graphForMidiNote->suspendProcessing(true);
            graphForMidiNote->clear();
            graphForMidiNote->releaseResources();

            midiNoteToProcessorGraphHash.erase(midiNoteNumber);
            std::cout << "erased graph. hash size now: " << midiNoteToProcessorGraphHash.size() << std::endl;
        }
    }
private:
    double sampleRate;
    int samplesPerBlock;
    int mainBusNumInputChannels;
    int mainBusNumOutputChannels;

    //each time a note is pressed, create a new graph and store it here so we can stop it when the note is released.
    std::map<int, std::unique_ptr<juce::AudioProcessorGraph>> midiNoteToProcessorGraphHash;
};



