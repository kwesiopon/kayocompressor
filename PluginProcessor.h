/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PeakDetectAlgo.h"
#include "GainSmoothing.h"


#define dB(x) 20.0 * ((x) >0.0001 ? log10(x) :-5.0)
#define db2mag(x) pow(10.0, (x) /20.0)

//==============================================================================
/**
*/
class AutoCompressorAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    AutoCompressorAudioProcessor();
    ~AutoCompressorAudioProcessor();
    //==============================================================================
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    

private:
    //==============================================================================
    AudioProcessorValueTreeState parameters;
    UndoManager undom;
    
    float fs,ratio,attackT,releaseT, threshold;
    
    //Gain
    float gain, gainS;
    
    //Gain Smoothing
    ScopedPointer<GainDynamics>  gainSmooth;
    
    //Peak Detectors
    ScopedPointer<PeakLvlDetector> leftLvlDetect, rightLvlDetect;
    float leftPeakO, rightPeakO,sumofPeak, soPS;
    
   
    
    
    //===============================================================================
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AutoCompressorAudioProcessor)
};
#endif
