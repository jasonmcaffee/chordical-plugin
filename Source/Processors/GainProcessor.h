//#include "ProcessorBase.h"

class GainProcessor : public ProcessorBase{
public:
    GainProcessor(){
        gain.setGainDecibels(0.0f);
    }

    void prepareToPlay(double sampleRate, int samplesPerBlock) override {
        //create a spec for the oscillator
        juce::dsp::ProcessSpec spec { sampleRate, static_cast<juce::uint32>(samplesPerBlock) };
        gain.prepare(spec);
    }

    void processBlock(juce::AudioSampleBuffer & buffer, juce::MidiBuffer&) override {
        juce::dsp::AudioBlock<float> block (buffer);
        juce::dsp::ProcessContextReplacing<float> context (block);
        gain.process(context);
    }

    void reset() override {
        gain.reset();
    }

    const juce::String getName() const override { return "Gain"; }

private:
    juce::dsp::Gain<float> gain;
};
