#include "./ProcessorBase.h"
#pragma once
class OscillatorProcessor  : public ProcessorBase {
public:
    OscillatorProcessor(float frequency){
        oscillator.setFrequency (frequency); //440.0f
        oscillator.initialise ([] (float x) { return std::sin (x); });
    }

    void setFrequency(float frequency){
        oscillator.setFrequency(frequency);
    }

    void prepareToPlay (double sampleRate, int samplesPerBlock) override {
//        juce::dsp::ProcessSpec spec { sampleRate, static_cast<juce::uint32> (samplesPerBlock) };
        juce::dsp::ProcessSpec spec { sampleRate, static_cast<juce::uint32> (samplesPerBlock), 2 };
        oscillator.prepare (spec);
    }

    void processBlock (juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override {
        juce::dsp::AudioBlock<float> block (buffer);
        juce::dsp::ProcessContextReplacing<float> context (block);
        oscillator.process (context);
    }

    void reset() override {
        oscillator.reset();
    }

    const juce::String getName() const override { return "Oscillator"; }

private:
    juce::dsp::Oscillator<float> oscillator;
};
