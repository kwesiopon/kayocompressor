
/*
 =============================================================================
   This file was auto-generated!
 
 
 
 
   It contains the basic framework code for a JUCE plugin editor.
 ==============================================================================
 */
#pragma once
#ifndef __JUCE_HEADER_419FC5D7D3F5212A__
#define __JUCE_HEADER_419FC5D7D3F5212A__
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
 */

class AutoCompressorAudioProcessorEditor  : public AudioProcessorEditor

{

public:
    enum{
        paramControlHeight = 40,
        paramLabelWidth    = 80,
        paramSliderWidth   = 300
    };
    
    
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    AutoCompressorAudioProcessorEditor (AutoCompressorAudioProcessor&processor, AudioProcessorValueTreeState& vts);
    ~AutoCompressorAudioProcessorEditor();
    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;



private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    AutoCompressorAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;
    
    
    
    ScopedPointer<SliderAttachment> threshAttachment;
    ScopedPointer<SliderAttachment> attackAttachment;
    ScopedPointer<SliderAttachment> ratioAttachment;
    ScopedPointer<SliderAttachment> releaseAttachment;
    ScopedPointer<SliderAttachment> gainAttachment;
    
    float normalizedValue;
    
    
    
    //Sliders
    Slider gainSlider,threshSlider,ratioSlider,attackSlider,releaseSlider;
    
    
    //Labels
    Label gainLabel,threshLabel,ratioLabel, attackLabel, releaseLabel;
    
    
    
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AutoCompressorAudioProcessorEditor)
};
#endif
