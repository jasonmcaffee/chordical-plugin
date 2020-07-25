#include <JuceHeader.h>

struct Sound : public SynthesiserSound {
    Sound() {}
    bool appliesToNote (int /*midiNoteNumber*/) override    { return true; }
    bool appliesToChannel (int /*midiChannel*/) override    { return true; }
};