//
// Created by Jason on 6/27/20.
//

#ifndef CHORDICAL_VST_SINEOSCILLATOR_H
#define CHORDICAL_VST_SINEOSCILLATOR_H

#include <JuceHeader.h>
class SineOscillator {

public:
    SineOscillator() {}

    void setFrequency (float frequency, float sampleRate){
        auto cyclesPerSample = frequency / sampleRate;
        angleDelta = cyclesPerSample * MathConstants<float>::twoPi;
    }
    forcedinline float getNextSample() noexcept {
        auto currentSample = std::sin (currentAngle);
        updateAngle();
        return currentSample;
    }

    forcedinline void updateAngle() noexcept {
        currentAngle += angleDelta;
        if(currentAngle >= MathConstants<float>::twoPi){
            currentAngle -= MathConstants<float>::twoPi;
        }
    }
//    void prepareToPlay(int, double sampleRate) override {
//
//    }

private:
    float currentAngle = 0.0f;
    float angleDelta = 0.0f;
};


#endif //CHORDICAL_VST_SINEOSCILLATOR_H
