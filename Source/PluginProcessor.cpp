//setup instructions
//https://www.youtube.com/watch?v=kxKEFTQRZPI
//https://www.youtube.com/watch?v=ddqwAJilnes

//cascading plugin with AudioProcessorGraph https://docs.juce.com/master/tutorial_audio_processor_graph.html

//midi in graph example: https://gist.github.com/ebenoist/263447603eb6449b14320fab381643d7

/**
 * https://forum.juce.com/t/audioprocessorgraph-buffer-mixing/10654/5
 * For anyone wondering, one can simply connect multiple AudioProcesspr outputs to a single AudioProcessor input via AudioProcessorGraph to sum the signals.
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Services/Synthesizer/Sine/SineWaveVoice.h"
#include "Processors/ProcessorBase.h"

using AudioGraphIOProcessor = juce::AudioProcessorGraph::AudioGraphIOProcessor;
using Node = juce::AudioProcessorGraph::Node;

//==============================================================================
PluginProcessor::PluginProcessor()
        : AudioProcessor (BusesProperties()
                                  .withInput  ("Input",  AudioChannelSet::stereo(), true)
                                  .withOutput ("Output", AudioChannelSet::stereo(), true)
),
          mainProcessor  (new juce::AudioProcessorGraph())
{
    autoChorder = AutoChorder{};

    synth.clearSounds();
    synth.clearVoices(); //clean up before next note?
    for (auto i = 0; i < 9; ++i){
        synth.addVoice (new SineWaveVoice());   // These voices will play our custom sine-wave sounds..
    }
    synth.addSound(new SineWaveSound());

    chordicalJuceSynth.setup();

    EventBus::eventBus().subscribe<WebAppLoadedMessage>([this](WebAppLoadedMessage message){
        std::cout << "Plugin processor got web app loaded" << std::endl;
        AppState appStateMessage = AppState { appState };
        auto json = convertAppStateLoadedToJSONString(appStateMessage);
        auto m = ToWebAppMessage {json};
        EventBus::eventBus().emitMessage(m);
    });

    EventBus::eventBus().subscribe<RequestToPlayMidiNotesMessage>([this](RequestToPlayMidiNotesMessage message){
        std::cout << " request to play midi notes. adding to queue" << std::endl;
        for(auto midiNoteData : message.data){
            requestToPlayMidiNoteDataQueue.push(midiNoteData);
        }
    });

    EventBus::eventBus().subscribe<RequestToStopMidiNotesMessage>([this](RequestToStopMidiNotesMessage message){
        for(auto midiNoteData: message.data){
            requestToStopMidiNoteDataQueue.push(midiNoteData);
        }
    });

    EventBus::eventBus().subscribe<RequestToSaveAppStateMessage>([this](RequestToSaveAppStateMessage message){
        std::cout << "request to save app state: " + message.data.state << std::endl;
        appState = message.data.state;
    });

    EventBus::eventBus().subscribe<RequestToGetAppStateMessage>([this](RequestToGetAppStateMessage message){
       std::cout << "request to get app state" << std::endl;
        AppState appStateMessage = AppState { appState };
        auto json = convertAppStateLoadedToJSONString(appStateMessage);
        auto m = ToWebAppMessage {json};
        EventBus::eventBus().emitMessage(m);
    });

    startTimer(1);
}

//processBlock must not be blocked by anything!  Can't call ui component and wait for it to do it's thing, so use a queue and a timer to emit messages to send to the web app.
void PluginProcessor::timerCallback() {
//    std::cout << "timer called" << std::endl;
    while(!sendPlayMidiNoteDataQueue.empty()){
        auto midiNoteData = sendPlayMidiNoteDataQueue.front();
        auto t = MidiNotePlayedMessage { midiNoteData };
        auto json = convertMidiNotePlayedToJSONString(t);
        auto s = ToWebAppMessage {json};
        EventBus::eventBus().emitMessage(s);
        sendPlayMidiNoteDataQueue.pop();
    }

    while(!sendStopMidiNoteDataQueue.empty()){
        auto midiNoteData = sendStopMidiNoteDataQueue.front();
        auto t = MidiNoteStoppedMessage { midiNoteData };
        auto json = convertMidiNoteStoppedToJSONString(t);
        auto s = ToWebAppMessage {json};
        EventBus::eventBus().emitMessage(s);
        sendStopMidiNoteDataQueue.pop();
    }
}

//destructor
PluginProcessor::~PluginProcessor(){}

//==============================================================================
/**
 * any pre-playback initialisation
 * @param sampleRate
 * @param samplesPerBlock
 */
void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //first demo using JUCE synthesizer and SineWaveSound/SineWaveVoice
    synth.setCurrentPlaybackSampleRate (sampleRate);
    chordicalJuceSynth.setCurrentPlaybackSampleRate(sampleRate);
    //our own synthesizer that uses audio processor graphs to chain effects.
    synthesizer.prepareToPlay(sampleRate, samplesPerBlock, getMainBusNumInputChannels(), getMainBusNumOutputChannels());
}


/**
 *
 * & param is used to pass references to variables defined in the calling function, or its ancestors, or at global level.
 * @param buffer
 * @param midiMessages
 */
void PluginProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages){
    ScopedNoDenormals noDenormals; //Helper class providing an RAII-based mechanism for temporarily disabling denormals on your CPU.  https://www.ccoderun.ca/juce/api/classjuce_1_1ScopedNoDenormals.html#details

    MidiBuffer processedMidi;
    int time;
    MidiMessage m;
    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);){
        if(m.isNoteOn()){
            sendPlayMidiNoteDataQueue.push(MidiNoteData {m.getNoteNumber(), m.getFloatVelocity() * 100});
        }else if(m.isNoteOff()){
            sendStopMidiNoteDataQueue.push(MidiNoteData {m.getNoteNumber(), m.getFloatVelocity() * 100});
        }
        //EventBus::eventBus().emitMessage(s);  //DON"T CALL UI COMPONENTS WITH UPDATES https://docs.juce.com/master/classChangeBroadcaster.html
    }

    //read off the queue to determine which midi notes to play.  e.g. web app will tell us to play 3 notes, and we'll do that by adding the notes to processedMidi
    //play
    while(!requestToPlayMidiNoteDataQueue.empty()){
        auto midiNoteData = requestToPlayMidiNoteDataQueue.front();
        std::cout << "from request to play queue midiNote: " << midiNoteData.midiNote << " velocity: " << midiNoteData.velocity << std::endl;
        processedMidi.addEvent(MidiMessage::noteOn(1, midiNoteData.midiNote, (juce::uint8) midiNoteData.velocity),0); //midi velocity as float has value 0 to 1.0f, so we must convert 127 to that format
        requestToPlayMidiNoteDataQueue.pop();
    }

    //stop
    while(!requestToStopMidiNoteDataQueue.empty()){
        auto midiNoteData = requestToStopMidiNoteDataQueue.front();
//        std::cout << "from request to stop queue midiNote: " << midiNoteData.midiNote << " velocity: " << midiNoteData.velocity << std::endl;
        processedMidi.addEvent(MidiMessage::noteOff(1, midiNoteData.midiNote),0);
        requestToStopMidiNoteDataQueue.pop();
    }

    midiMessages.clear();
    midiMessages.swapWith(processedMidi);

    chordicalJuceSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================

const String PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool PluginProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool PluginProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double PluginProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int PluginProcessor::getCurrentProgram()
{
    return 0;
}

void PluginProcessor::setCurrentProgram (int index)
{
}

const String PluginProcessor::getProgramName (int index)
{
    return {};
}

void PluginProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================

void PluginProcessor::releaseResources()
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
bool PluginProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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
bool PluginProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new ChordicalAudioProcessorEditor (*this);
}

//==============================================================================
//called when closing the app
void PluginProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    String myString = appState;
    MemoryOutputStream stream(destData, false);
    stream.writeText (myString, true, true, nullptr);
    std::cout << "getStateInformation: " + myString << std::endl;
}
//called when opening the app
void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    String myString = String::createStringFromData (data, sizeInBytes);
    std::cout << "setStateInformation: " + myString << std::endl;

    appState = myString.toStdString();
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginProcessor();
}


//    auto totalNumInputChannels  = getTotalNumInputChannels();
//    auto totalNumOutputChannels = getTotalNumOutputChannels();
// In case we have more outputs than inputs, this code clears any output channels that didn't contain input data, (because these aren't guaranteed to be empty - they may contain garbage). This is here to avoid people getting screaming feedback
// when they first compile a plugin, but obviously you don't need to keep this code if your algorithm always overwrites all the output channels.
//    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i){
//        buffer.clear (i, 0, buffer.getNumSamples());
//    }

//original demo using the juce synthesizer to play SineWaveVoice/SineWaveSound.
//    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

//newest
//    synthesizer.processBlock(buffer, midiMessages);
//    chordicalJuceSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());