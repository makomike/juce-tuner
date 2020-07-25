/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <math.h>

//==============================================================================
Pitchdetect_autocorrelateAudioProcessorEditor::Pitchdetect_autocorrelateAudioProcessorEditor (Pitchdetect_autocorrelateAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible (infoLabel);
    infoLabel.setText ("Text input:", juce::dontSendNotification);
    infoLabel.setColour (juce::Label::textColourId, juce::Colours::orange);
    infoLabel.setJustificationType (juce::Justification::centred);
    infoLabel.setFont (juce::Font (20.0f, juce::Font::bold));
    
    setSize (400, 300);
    startTimer (50);
}

Pitchdetect_autocorrelateAudioProcessorEditor::~Pitchdetect_autocorrelateAudioProcessorEditor()
{
}

//==============================================================================
void Pitchdetect_autocorrelateAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Tuner", getLocalBounds(), Justification::centred, 1);
}

void Pitchdetect_autocorrelateAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
        infoLabel.setBounds (0,  50, getWidth(),  30);
}

template <typename T1, typename T2>
T1 findClosestKey(const std::map<T1, T2> & data, T1 key)
{
    if (data.size() == 0) {
        throw std::out_of_range("Received empty map.");
    }

    auto lower = data.lower_bound(key);

    if (lower == data.end()) // If none found, return the last one.
        return std::prev(lower)->first;

    if (lower == data.begin())
        return lower->first;

    // Check which one is closest.
    auto previous = std::prev(lower);
    if ((key - previous->first) < (lower->first - key))
        return previous->first;

    return lower->first;
}

int noteFromPitch(float frequency) {
    int noteNum = 12 * (log(frequency / 440) / log(2));
    noteNum = round(noteNum) + 69;
    return noteNum;
}

float frequencyFromNoteNumber(float note) {
    return 440 * pow(2, (note - 69) / 12);
}

float centsOffFromPitch(float frequency, float note) {
    return floor(1200 * (float)log(frequency / frequencyFromNoteNumber(note)) / log(2));
}

void Pitchdetect_autocorrelateAudioProcessorEditor::timerCallback()
{
        Pitchdetect_autocorrelateAudioProcessor& ourProcessor = getProcessor();
        double key = ourProcessor.pitch / 2;
        
        if(key <= 0.0f)
        {
            infoLabel.setText("--",juce::dontSendNotification);
            return;
        }
       
        //TODO PUT CORRECT MAPPING HERE
        //Middle C
        std::map<double, std::string> data = {{261.63, "C"}, {277.1, "C#"}, {293.66, "D"},{311.13, "Eb"} ,{329.63, "E#"} ,{349.23, "F"} ,{369.99, "F#"},{210.60, "G"},{210.60, "G#"},{440.00, "A"} ,{466.16, "Bb"},{493.88, "B"}};
        double nearestKey = findClosestKey(data, key);
        double cents = key - nearestKey;

    

        //Mapping without frequency

        std::array<String, 12> not = { "B","C","C#","D","Eb","E","F","F#","G","G#","A","Bb"};

        int currentKey = noteFromPitch(key);
        int Note = frequencyFromNoteNumber(currentKey);
        float centsOffPitch = centsOffFromPitch(currentKey, Note);

      //  infoLabel.setText((String)data[nearestKey] + " cents: " + (String)cents,juce::dontSendNotification);
    //    infoLabel.setText((String)not[Note % 12] + " cents: " + (String)cents, juce::dontSendNotification);
        infoLabel.setText((String)not[currentKey % 12] + " frequency: " + (String)key,juce::dontSendNotification);
 }


