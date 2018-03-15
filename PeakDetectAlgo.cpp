/*
  ==============================================================================

    PeakDetectAlgo.cpp
    Created: 31 Dec 2017 6:50:05am
    Author:  Adrian Opon

  ==============================================================================
*/

#include "PeakDetectAlgo.h"


PeakLvlDetector::PeakLvlDetector(float sampleRate) {
    setDetector(sampleRate);
}

PeakLvlDetector::~PeakLvlDetector() {}

float PeakLvlDetector::tick(float inputSample) {
    inputAbs = fabs(inputSample);
    
    if (inputAbs > peakOutput) {
        b0 = b0Attack;
    }
    else {
        b0 = b0Release;
    }
    
    // Simplified filter equation (out = b0 * input + a1 * lastOut)
    peakOutput += b0 * (inputAbs - peakOutput);
    
    return peakOutput;
}

void PeakLvlDetector::setDetector(float sampleRate) {
    fs = sampleRate;
    peakOutput = 0.f;
    
    // set coefficients for leaky integrator
    b0Attack = 1.f;
    a1 = expf(-1 / (releaseTime * fs));
    b0Release = 1.f - a1;
}
