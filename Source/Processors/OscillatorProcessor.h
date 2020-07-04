//#include "ProcessorBase.h"

class OscillatorProcessor  : public ProcessorBase
{
public:
    OscillatorProcessor()
    {
        oscillator.setFrequency (440.0f);
        oscillator.initialise ([] (float x) { return std::sin (x); });
    }

    void prepareToPlay (double sampleRate, int samplesPerBlock) override
    {
        juce::dsp::ProcessSpec spec { sampleRate, static_cast<juce::uint32> (samplesPerBlock) };
        oscillator.prepare (spec);
    }

    void processBlock (juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override
    {
        juce::dsp::AudioBlock<float> block (buffer);
        juce::dsp::ProcessContextReplacing<float> context (block);
        oscillator.process (context);
    }

    void reset() override
    {
        oscillator.reset();
    }

    const juce::String getName() const override { return "Oscillator"; }

private:
    juce::dsp::Oscillator<float> oscillator;
};
