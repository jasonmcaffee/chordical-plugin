#include <JuceHeader.h>

struct SineWaveSound : public SynthesiserSound {
    SineWaveSound() {}

    bool appliesToNote (int /*midiNoteNumber*/) override    { return true; }
    bool appliesToChannel (int /*midiChannel*/) override    { return true; }
};