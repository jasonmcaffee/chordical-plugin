#include <JuceHeader.h>
#include "./Sound.h"
#include "../../../Processors/ChordicalOscillatorGraph.h"

#pragma once




/**
 * Responsible for filling the AudioBuffer with sound based on angle and number of samples passed to the renderNextBlock function.
 */
struct Voice  : public SynthesiserVoice {
    Voice() {
        std::cout << "Voice constructor called" << std::endl;
    }

    bool canPlaySound (SynthesiserSound* sound) override{
        return dynamic_cast<Voice*> (sound) != nullptr;
    }

    void startNote (int midiNoteNumber, float velocity, SynthesiserSound*, int /*currentPitchWheelPosition*/) override{
        std::cout << "startNote called" << std::endl;
//        this->graph = createGraph(this->getSampleRate(), this->get)
        oscGraph->setMidiNote(midiNoteNumber);
    }

    void stopNote (float /*velocity*/, bool allowTailOff) override {
    }

    void pitchWheelMoved (int /*newValue*/) override                              {}
    void controllerMoved (int /*controllerNumber*/, int /*newValue*/) override    {}

    void renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override{
        for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
            outputBuffer.clear (i, 0, outputBuffer.getNumSamples());
        MidiBuffer midiBuffer;
        oscGraph->processBlock(outputBuffer, midiBuffer);
    }

    using SynthesiserVoice::renderNextBlock;

private:
    std::unique_ptr<ChordicalOscillatorGraph> oscGraph;
};