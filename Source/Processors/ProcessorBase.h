#include <JuceHeader.h>
#pragma once
/**
 * Base class that all processors (gain, osc, filter, etc) will derive from.
 */
class ProcessorBase  : public juce::AudioProcessor{
public:
    ProcessorBase()  {}

    void prepareToPlay (double, int) override {}
    void releaseResources() override {}
    void processBlock (juce::AudioSampleBuffer&, juce::MidiBuffer&) override {}

    juce::AudioProcessorEditor* createEditor() override { return nullptr; }
    bool hasEditor() const override { return false; }

    const juce::String getName() const override { return {}; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0; }

    int getNumPrograms() override { return 0; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const juce::String getProgramName (int) override { return {}; }
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock&) override {}
    void setStateInformation (const void*, int) override {}

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProcessorBase)
};
