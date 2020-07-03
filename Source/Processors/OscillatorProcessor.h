#include "ProcessorBase.h"

class OscillatorProcessor : public ProcessorBase{
public:
    OscillatorProcessor(){
        oscillator.setFrequency(440.0f);
        oscillator.initialise([](float x) { return std::sin (x); });
    }

    void prepareToPlay(double sampleRate, int samplesPerBlock) override {

    }


    const juce::String getName() const override { return "Oscillator"; }
private:
    juce::dsp::Oscillator<float> oscillator;
};
