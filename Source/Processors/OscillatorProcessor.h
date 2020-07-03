#include "ProcessorBase.h"

class OscillatorProcessor : public ProcessorBase{
public:
    const juce::String getName() const override { return "Oscillator"; }
private:
};
