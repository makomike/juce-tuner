/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Pitchdetect_autocorrelateAudioProcessorEditor  : public AudioProcessorEditor, public Timer
{
public:
    Pitchdetect_autocorrelateAudioProcessorEditor (Pitchdetect_autocorrelateAudioProcessor&);
    ~Pitchdetect_autocorrelateAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Pitchdetect_autocorrelateAudioProcessor& processor;

    Label infoLabel;
    Label flatLabel;
    Label sharpLabel;
    Pitchdetect_autocorrelateAudioProcessor& getProcessor() const
         {
             return static_cast<Pitchdetect_autocorrelateAudioProcessor&> (processor);
         }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Pitchdetect_autocorrelateAudioProcessorEditor)
};
