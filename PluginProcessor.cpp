/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
AutoCompressorAudioProcessor::AutoCompressorAudioProcessor()
: parameters (*this,&undom)
{
    
    parameters.createAndAddParameter("threshold", // parameter ID
                                     "Threshold", // parameter name
                                     String(), // parameter label
                                     NormalisableRange<float>(0.0f, 1.0f), //range
                                     0.0f, //default value
                                     nullptr,
                                     nullptr);
    parameters.createAndAddParameter("attack",
                                     "Attack",
                                     String(),
                                     NormalisableRange<float>(0.0f, 1.0f),
                                     0.0f,
                                     nullptr,
                                     nullptr);
    parameters.createAndAddParameter("release",
                                     "Release",
                                     String(),
                                     NormalisableRange<float> (0.0f,1.0f),
                                     0.0f,nullptr,
                                     nullptr);
    parameters.createAndAddParameter("ratio",
                                     "Ratio",
                                     String(),
                                     NormalisableRange<float> (1.0f,10.0f),
                                     0.0f,nullptr,
                                     nullptr);
   
    
    parameters.state = ValueTree(Identifier("ComprGadgets"));
    
    
    
}

AutoCompressorAudioProcessor::~AutoCompressorAudioProcessor()
{
}
//==============================================================================


//==============================================================================
const String AutoCompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AutoCompressorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AutoCompressorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AutoCompressorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AutoCompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AutoCompressorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AutoCompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AutoCompressorAudioProcessor::setCurrentProgram (int index)
{
}

const String AutoCompressorAudioProcessor::getProgramName (int index)
{
    return {};
}

void AutoCompressorAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void AutoCompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    fs = sampleRate;
    gain = 1.0f;
    
    attackT = *parameters.getRawParameterValue("attack");
    releaseT = *parameters.getRawParameterValue("release");
    ratio = *parameters.getRawParameterValue("ratio");
    threshold = *parameters.getRawParameterValue("threshold");
    
    
    
    if (leftLvlDetect == nullptr && rightLvlDetect == nullptr){
        leftLvlDetect = new PeakLvlDetector(sampleRate);
        rightLvlDetect = new PeakLvlDetector(sampleRate);
    } else {
        leftLvlDetect->setDetector(sampleRate);
        rightLvlDetect->setDetector(sampleRate);
    }
    if (gainSmooth ==nullptr){
        
        gainSmooth = new GainDynamics(sampleRate,attackT,releaseT);
        
    }else {
        gainSmooth->setDetector(sampleRate);
    }
    
}

void AutoCompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AutoCompressorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void AutoCompressorAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
 

    for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    float* leftChannelData = buffer.getWritePointer(0);
    float* rightChannelData = buffer.getWritePointer(1);

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int i = 0; i< buffer.getNumSamples();i++){
        //Peak detector
        leftPeakO = leftLvlDetect->tick(leftChannelData[i]);
        rightPeakO = rightLvlDetect->tick(rightChannelData[i]);
        sumofPeak =(leftPeakO + rightPeakO) * 0.5f;
        
        //the peak next needs to be translated to sound levels
        soPS = dB(sumofPeak);
        
        //Next the gain needs to be calculated
        if (soPS < threshold){
            
            gainS = 0.0f;
        }else {
            
            gainS = -(soPS - threshold) * (1.0f - 1.0f/ratio);
        }
        
        // attack and release gain dynamics
        gainS = gainSmooth->tick(gainS);
        
        //Convert db to linear
        leftChannelData[i] *= gain;
        rightChannelData[i] *= gain;
        
        
        
    }
// ..do something to the data...
    
}

//==============================================================================
bool AutoCompressorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AutoCompressorAudioProcessor::createEditor()
{ 
    return new  AutoCompressorAudioProcessorEditor (*this,parameters);
}

//==============================================================================
void AutoCompressorAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    ScopedPointer<XmlElement> xml (parameters.state.createXml());
    copyXmlToBinary (*xml, destData);
}

void AutoCompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.state = ValueTree::fromXml (*xmlState);
}
//==============================================================================

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AutoCompressorAudioProcessor();
}
  //============================================================================

