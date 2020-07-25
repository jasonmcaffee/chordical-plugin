#include "./ProcessorBase.h"
#include "./GainProcessor.h"
#include "./OscillatorProcessor.h"
#include "./FilterProcessor.h"

#pragma once
using AudioGraphIOProcessor = juce::AudioProcessorGraph::AudioGraphIOProcessor;
using Node = juce::AudioProcessorGraph::Node;


//inline float convertMidiNoteNumberToFrequency(int midiNoteNumber){
//    auto a = 440.0;
////    auto freq = (a / 32) * pow(2, ((midiNoteNumber - 9) / 12) );
////    float freq =  a * pow (2.0, (midiNoteNumber - 69) / 12);
//    double freq = juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
//    std::cout << " midiNoteNumber: " << midiNoteNumber << " frequency: " << freq << std::endl;
//    return freq;
//}

class ChordicalOscillatorGraph  : public ProcessorBase
{
public:
    ChordicalOscillatorGraph(){
        std::cout << "chordicalOscillatorGraph constructor" << std::endl;
    }

    void createGraph(double sampleRate, int blockSize, int mainBusNumInputChannels, int mainBusNumOutputChannels){

        std::cout << "createGraph called" << std::endl;

//        std::unique_ptr<juce::AudioProcessorGraph> mainProcessor = std::make_unique<juce::AudioProcessorGraph>();
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

        //create some nodes/processors to add to our main processor.
        auto gainNode = mainProcessor->addNode(std::make_unique<GainProcessor>());

        oscillatorProcessor = std::make_unique<OscillatorProcessor>(440);

//        auto oscillatorNode = mainProcessor->addNode(std::make_unique<OscillatorProcessor>(440));
        auto oscillatorNode = mainProcessor->addNode(
                reinterpret_cast<std::unique_ptr<AudioProcessor> &&>(oscillatorProcessor));

//    auto filterNode = mainProcessor->addNode(std::make_unique<FilterProcessor>());

        //set the play configuration for each node
        gainNode->getProcessor()->setPlayConfigDetails(mainBusNumInputChannels, mainBusNumOutputChannels, sampleRate, blockSize);
        oscillatorNode->getProcessor()->setPlayConfigDetails(mainBusNumInputChannels, mainBusNumOutputChannels, sampleRate, blockSize);
//    filterNode->getProcessor()->setPlayConfigDetails(mainBusNumInputChannels, mainBusNumOutputChannels, sampleRate, blockSize);

        //connect the nodes together. add a connection for each of the 2 channels.
        for(int channel = 0; channel < 2; ++channel){
            mainProcessor->addConnection({ {audioInputNode->nodeID, channel}, {oscillatorNode->nodeID, channel}});
            mainProcessor->addConnection({ {oscillatorNode->nodeID, channel}, {gainNode->nodeID, channel} });
//        mainProcessor->addConnection({ {gainNode->nodeID, channel}, {filterNode->nodeID, channel} });
//        mainProcessor->addConnection({ {filterNode->nodeID, channel}, {audioOutputNode->nodeID, channel} });
            mainProcessor->addConnection({ {gainNode->nodeID, channel}, {audioOutputNode->nodeID, channel} });
        }

        //connect the midi nodes
        mainProcessor->addConnection({ {midiInputNode->nodeID, juce::AudioProcessorGraph::midiChannelIndex}, {midiOutputNode->nodeID, juce::AudioProcessorGraph::midiChannelIndex} });

        //enable buses on all nodes
        for(auto node : mainProcessor->getNodes()){
            node->getProcessor()->enableAllBuses();
        }
    }

    void prepareToPlay (double sampleRate, int samplesPerBlock) override
    {
        createGraph(sampleRate, samplesPerBlock, getNumInputChannels(), getNumOutputChannels());
    }

    void setMidiNote(int midiNoteNumber){
        auto freq = convertMidiNoteNumberToFrequency(midiNoteNumber);
        oscillatorProcessor->setFrequency(freq);
    }

    void processBlock (juce::AudioSampleBuffer& buffer, juce::MidiBuffer& midiBuffer) override
    {
       mainProcessor->processBlock(buffer, midiBuffer);
    }

    void reset() override
    {
        mainProcessor.reset();
    }

    const juce::String getName() const override { return "ChordicalOscillatorGraph"; }

private:
    std::unique_ptr<juce::AudioProcessorGraph> mainProcessor;
    std::unique_ptr<OscillatorProcessor> oscillatorProcessor;
};