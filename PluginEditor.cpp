/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
AutoCompressorAudioProcessorEditor::AutoCompressorAudioProcessorEditor (AutoCompressorAudioProcessor& processor, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (processor),processor(processor),valueTreeState(vts)
{
        addAndMakeVisible (threshSlider);
    threshAttachment = new SliderAttachment (valueTreeState,"threshold", threshSlider);
    
    addAndMakeVisible(attackSlider);
    attackAttachment = new SliderAttachment(valueTreeState,"attack",attackSlider);
    
    addAndMakeVisible(releaseSlider);
    releaseAttachment = new SliderAttachment(valueTreeState,"release",releaseSlider);
    
    addAndMakeVisible(ratioSlider);
    ratioAttachment = new SliderAttachment(valueTreeState,"ratio",ratioSlider);
    
    addAndMakeVisible(gainSlider);
    gainAttachment = new SliderAttachment(valueTreeState,"gain", gainSlider);
    
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    setSize (paramSliderWidth+paramLabelWidth,paramControlHeight * 2 );
    
    
}

AutoCompressorAudioProcessorEditor::~AutoCompressorAudioProcessorEditor()
{
    
    
     deleteAllChildren();
}

//==============================================================================
void AutoCompressorAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
   
}

void AutoCompressorAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    Rectangle<int> r = getLocalBounds();
    {
        
    Rectangle<int> gainRect = r.removeFromTop(paramControlHeight);
        gainSlider.setBounds(gainRect);
        gainLabel.setBounds(gainRect.removeFromLeft(paramLabelWidth));
    Rectangle<int> threshRect = r.removeFromTop(paramControlHeight-10);
        threshSlider.setBounds(threshRect);
    Rectangle<int> attackRect = r.removeFromTop(paramControlHeight-20);
        attackSlider.setBounds(attackRect);
    Rectangle<int> ratioRect = r.removeFromTop(paramControlHeight-30);
        ratioSlider.setBounds(ratioRect);
    Rectangle<int> releaseRect = r.removeFromTop(paramControlHeight-40);
        releaseSlider.setBounds(releaseRect);
        //
    }
}


