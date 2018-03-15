/*
  ==============================================================================

    PeakDetectAlgo.h
    Created: 31 Dec 2017 6:50:05am
    Author:  Adrian Opon

  ==============================================================================
*/


#ifndef BU_P05_Compressor_PeakLevelDetector_h
#define BU_P05_Compressor_PeakLevelDetector_h

#include <math.h>

class PeakLvlDetector {
public:
    PeakLvlDetector(float sampleRate);
    ~PeakLvlDetector();
    
    float tick(float inputSample);
    void setDetector(float sampleRate);
    
private:
    float fs, inputAbs, peakOutput;
    float b0Attack, b0Release, b0, a1;
    float releaseTime = 0.100f;     // seconds
};

#endif
