//setup instructions
//https://www.youtube.com/watch?v=kxKEFTQRZPI
//https://www.youtube.com/watch?v=ddqwAJilnes

//cascading plugin with AudioProcessorGraph https://docs.juce.com/master/tutorial_audio_processor_graph.html

//midi in graph example: https://gist.github.com/ebenoist/263447603eb6449b14320fab381643d7

/**
 * https://forum.juce.com/t/audioprocessorgraph-buffer-mixing/10654/5
 * For anyone wondering, one can simply connect multiple AudioProcesspr outputs to a single AudioProcessor input via AudioProcessorGraph to sum the signals.
 */

#include "ChordicalAudioProcessor.h"
#include "Components/PluginEditor.h"
#include "Services/Synthesizer/Sine/SineWaveVoice.h"
#include "Processors/ProcessorBase.h"
#include "Processors/OscillatorProcessor.h"
#include "Processors/GainProcessor.h"
#include "Processors/FilterProcessor.h"

using AudioGraphIOProcessor = juce::AudioProcessorGraph::AudioGraphIOProcessor;
using Node = juce::AudioProcessorGraph::Node;

//==============================================================================
ChordicalAudioProcessor::ChordicalAudioProcessor()
        : AudioProcessor (BusesProperties()
                                  .withInput  ("Input",  AudioChannelSet::stereo(), true)
                                  .withOutput ("Output", AudioChannelSet::stereo(), true)
),
          mainProcessor  (new juce::AudioProcessorGraph())
{
    synth.clearSounds();
    synth.clearVoices(); //clean up before next note?
    for (auto i = 0; i < 4; ++i){
        synth.addVoice (new SineWaveVoice());   // These voices will play our custom sine-wave sounds..

    }
    synth.addSound(new SineWaveSound());

}

//destructor
ChordicalAudioProcessor::~ChordicalAudioProcessor(){}

//==============================================================================
/**
 * any pre-playback initialisation
 * @param sampleRate
 * @param samplesPerBlock
 */
void ChordicalAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //first demo using JUCE synthesizer and SineWaveSound/SineWaveVoice
    synth.setCurrentPlaybackSampleRate (sampleRate);

    //our own synthesizer that uses audio processor graphs to chain effects.
    synthesizer.prepareToPlay(sampleRate, samplesPerBlock, getMainBusNumInputChannels(), getMainBusNumOutputChannels());

    initializeGraph();
//    updateGraph();
}


/**
 *
 * & param is used to pass references to variables defined in the calling function, or its ancestors, or at global level.
 * @param buffer
 * @param midiMessages
 */
void ChordicalAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages){
    ScopedNoDenormals noDenormals; //Helper class providing an RAII-based mechanism for temporarily disabling denormals on your CPU.  https://www.ccoderun.ca/juce/api/classjuce_1_1ScopedNoDenormals.html#details
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    // In case we have more outputs than inputs, this code clears any output channels that didn't contain input data, (because these aren't guaranteed to be empty - they may contain garbage). This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i){
        buffer.clear (i, 0, buffer.getNumSamples());
    }

    //original demo using the juce synthesizer to play SineWaveVoice/SineWaveSound.
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    //second demo using an AudioProcessorGraph that is created and maintained in this class.
    //We want to move this into our own synthesizer.
    //generates a constant tone via OscillatorProcessor, which has it's frequency hard coded.
    //mainProcessor->processBlock(buffer, midiMessages);

    //moving processing to our own custom synthesizer.
    synthesizer.processBlock(buffer, midiMessages);
}


void ChordicalAudioProcessor::initializeGraph(){

    auto mainBusNumInputChannels = getMainBusNumInputChannels();
    auto mainBusNumOutputChannels = getMainBusNumOutputChannels();
    auto sampleRate = getSampleRate();
    auto blockSize = getBlockSize();
    std::cout << "initializeGraph. mainBusNumInputChannels: " << mainBusNumInputChannels << ", mainBusNumOutputChannels: " << mainBusNumOutputChannels << std::endl;

    //delete all nodes and connections
    mainProcessor->clear();

    //create an audio graph processor
    mainProcessor->setPlayConfigDetails(mainBusNumInputChannels, mainBusNumOutputChannels, sampleRate, blockSize);
    mainProcessor->prepareToPlay(getSampleRate(), getBlockSize());

    //https://stackoverflow.com/questions/37514509/advantages-of-using-stdmake-unique-over-new-operator
    audioInputNode  = mainProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::audioInputNode));
    audioOutputNode = mainProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::audioOutputNode));
    midiInputNode   = mainProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::midiInputNode));
    midiOutputNode  = mainProcessor->addNode (std::make_unique<AudioGraphIOProcessor> (AudioGraphIOProcessor::midiOutputNode));

//    connectAudioNodes();
//    connectMidiNodes();
    auto gainNode = mainProcessor->addNode(std::make_unique<GainProcessor>());
    auto oscillatorNode = mainProcessor->addNode(std::make_unique<OscillatorProcessor>());
    auto filterNode = mainProcessor->addNode(std::make_unique<FilterProcessor>());

    gainNode->getProcessor()->setPlayConfigDetails(mainBusNumInputChannels, mainBusNumOutputChannels, sampleRate, blockSize);
    oscillatorNode->getProcessor()->setPlayConfigDetails(mainBusNumInputChannels, mainBusNumOutputChannels, sampleRate, blockSize);
    filterNode->getProcessor()->setPlayConfigDetails(mainBusNumInputChannels, mainBusNumOutputChannels, sampleRate, blockSize);

    //add a connection for 2 channels per processor
    for(int channel = 0; channel < 2; ++channel){
        mainProcessor->addConnection({ {audioInputNode->nodeID, channel}, {oscillatorNode->nodeID, channel}});
        mainProcessor->addConnection({ {oscillatorNode->nodeID, channel}, {gainNode->nodeID, channel} });
        mainProcessor->addConnection({ {gainNode->nodeID, channel}, {filterNode->nodeID, channel} });
        mainProcessor->addConnection({ {filterNode->nodeID, channel}, {audioOutputNode->nodeID, channel} });
    }



    connectMidiNodes();
    //enable buses on all nodes
    for(auto node : mainProcessor->getNodes()){
        node->getProcessor()->enableAllBuses();
    }

}

std::unique_ptr<juce::AudioProcessorGraph> createAndInitializeOscGraph(int mainBusNumInputChannels, int mainBusNumOutputChannels, double sampleRate, int blockSize){
//    auto graph = new juce::AudioProcessorGraph();
    auto graph = std::make_unique<juce::AudioProcessorGraph>();

    return graph;
}




void ChordicalAudioProcessor::connectAudioNodes(){
    for(int channel = 0; channel < 2; ++channel){
        mainProcessor->addConnection({ {audioInputNode->nodeID, channel}, {audioOutputNode->nodeID, channel}});
    }
}

void ChordicalAudioProcessor::connectMidiNodes(){
    mainProcessor->addConnection({ {midiInputNode->nodeID, juce::AudioProcessorGraph::midiChannelIndex}, {midiOutputNode->nodeID, juce::AudioProcessorGraph::midiChannelIndex} });
}


//==============================================================================

const String ChordicalAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ChordicalAudioProcessor::acceptsMidi() const
{
    return true;
//#if JucePlugin_WantsMidiInput
//    return true;
//#else
//    return false;
//#endif
}

bool ChordicalAudioProcessor::producesMidi() const
{
    return true;
//#if JucePlugin_ProducesMidiOutput
//    return true;
//#else
//    return false;
//#endif
}

bool ChordicalAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double ChordicalAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ChordicalAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int ChordicalAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ChordicalAudioProcessor::setCurrentProgram (int index)
{
}

const String ChordicalAudioProcessor::getProgramName (int index)
{
    return {};
}

void ChordicalAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================

void ChordicalAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    mainProcessor->releaseResources();
}

#ifndef JucePlugin_PreferredChannelConfigurations
/**
 * Since we are dealing with a plugin, we need to implement the isBusesLayoutSupported() callback to inform the plugin host or DAW about which channel sets we support.
 * In this example we decide to only support mono-to-mono and stereo-to-stereo configurations
 * @param layouts
 * @return
 */
bool ChordicalAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainInputChannelSet()  == juce::AudioChannelSet::disabled()
        || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::disabled())
        return false;

    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
}
#endif

//==============================================================================
bool ChordicalAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ChordicalAudioProcessor::createEditor()
{
    return new ChordicalAudioProcessorEditor (*this);
}

//==============================================================================
void ChordicalAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ChordicalAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChordicalAudioProcessor();
}
