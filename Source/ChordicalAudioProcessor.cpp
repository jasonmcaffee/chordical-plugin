/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

//https://www.youtube.com/watch?v=kxKEFTQRZPI
//https://www.youtube.com/watch?v=ddqwAJilnes

#include "ChordicalAudioProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ChordicalAudioProcessor::ChordicalAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
        : AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                                  .withInput  ("Input",  AudioChannelSet::stereo(), true)
#endif
                                  .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
)
#endif
{

    synth.clearSounds();
    synth.clearVoices(); //clean up before next note?
    for (auto i = 0; i < 4; ++i){
        synth.addVoice (new SineWaveVoice());   // These voices will play our custom sine-wave sounds..

    }
    synth.addSound(new SineWaveSound());

}

ChordicalAudioProcessor::~ChordicalAudioProcessor()
{
}

//==============================================================================
void ChordicalAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
//    synthAudioSource.prepareToPlay(samplesPerBlock, sampleRate);
    synth.setCurrentPlaybackSampleRate (sampleRate);


}


void ChordicalAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages){
//    std::cout << "process block";R
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

//    // This is the place where you'd normally do the guts of your plugin's
//    // audio processing...
//    // Make sure to reset the state if your inner loop is processing
//    // the samples and the outer loop is handling the channels.
//    // Alternatively, you can process the samples with the channels
//    // interleaved by keeping the same state.
//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        auto* channelData = buffer.getWritePointer (channel);
//
//
//        // ..do something to the data...
//    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}
//
//void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
//{
//    if (angleDelta != 0.0){
//        if (tailOff > 0.0){
//            while (--numSamples >= 0){
//                auto currentSample = (float)(std::sin(currentAngle) * level * tailOff);
//
//                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
//                    outputBuffer.addSample(i, startSample, currentSample);
//
//                currentAngle += angleDelta;
//                ++startSample;
//
//                tailOff *= 0.99;
//
//                if (tailOff <= 0.005){
//                    clearCurrentNote();
//                    angleDelta = 0.0;
//                    break;
//                }
//            }
//        }
//        else{
//            while (--numSamples >= 0){
//                auto currentSample = (float)(std::sin(currentAngle) * level);
//
//                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
//                    outputBuffer.addSample(i, startSample, currentSample);
//
//                currentAngle += angleDelta;
//                ++startSample;
//            }
//        }
//    }
//}
//void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
//{
//
//}


//==============================================================================

const String ChordicalAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ChordicalAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool ChordicalAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
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
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ChordicalAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
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
