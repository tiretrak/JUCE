/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ReverbAudioProcessorEditor::ReverbAudioProcessorEditor (ReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(460, 300);
	setResizable(false, true);

	//wait for prepare to play to be done.
	//while (processor.donePrepareToPlay != 1);

	//the constructor gets called every time you click on the plugin so initialize everything at prepare to play
	//set up parameters for the slider
	drySlider.setSliderStyle(Slider::LinearBarVertical);
	drySlider.setRange(0.0, 1.0, 0.01);
	drySlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	//these methods don't work on Mac, only Windows...
    //drySlider.setPopupDisplayEnabled(true, this);
	drySlider.setTextValueSuffix(" Dry");

	wetSlider.setSliderStyle(Slider::LinearBarVertical);
	wetSlider.setRange(0.0, 1.0, 0.01);
	wetSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	//wetSlider.setPopupDisplayEnabled(true, this);
	wetSlider.setTextValueSuffix(" Wet");

	timeSlider.setSliderStyle(Slider::LinearBarVertical);
	timeSlider.setRange(0.0, 1.0, 0.01);
	timeSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	//timeSlider.setPopupDisplayEnabled(true, this);
	timeSlider.setTextValueSuffix(" Dec");

	dampSlider.setSliderStyle(Slider::LinearBarVertical);
	dampSlider.setRange(0.0, 1.0, 0.01);
	dampSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	//dampSlider.setPopupDisplayEnabled(true, this);
	dampSlider.setTextValueSuffix(" Damp");

	feedbackSlider.setSliderStyle(Slider::LinearBarVertical);
	feedbackSlider.setRange(0.0, 1.0, 0.01);
	feedbackSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	//feedbackSlider.setPopupDisplayEnabled(true, this);
	feedbackSlider.setTextValueSuffix(" Feedback");

	delaySlider.setSliderStyle(Slider::LinearBarVertical);
	delaySlider.setRange(0.0, 1.0, 0.01);
	delaySlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	//delaySlider.setPopupDisplayEnabled(true, this);
	delaySlider.setTextValueSuffix(" Delay");

	oscAmtSlider.setSliderStyle(Slider::LinearBarVertical);
	oscAmtSlider.setRange(0.0, 1.0, 0.01);
	oscAmtSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	//oscAmtSlider.setPopupDisplayEnabled(true, this);
	oscAmtSlider.setTextValueSuffix(" Modulation");

	oscFreqSlider.setSliderStyle(Slider::LinearBarVertical);
	oscFreqSlider.setRange(0.0, 1.0, 0.01);
	oscFreqSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	//oscFreqSlider.setPopupDisplayEnabled(true, this);
	oscFreqSlider.setTextValueSuffix(" Frequency");

	feedback2Slider.setSliderStyle(Slider::LinearBarVertical);
	feedback2Slider.setRange(0.0, 1.0, 0.01);
	feedback2Slider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	//feedback2Slider.setPopupDisplayEnabled(true, this);
	feedback2Slider.setTextValueSuffix(" Feedback");

	delay2Slider.setSliderStyle(Slider::LinearBarVertical);
	delay2Slider.setRange(0.0, 1.0, 0.01);
	delay2Slider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	//delay2Slider.setPopupDisplayEnabled(true, this);
	delay2Slider.setTextValueSuffix(" Delay");

	oscAmt2Slider.setSliderStyle(Slider::LinearBarVertical);
	oscAmt2Slider.setRange(0.0, 1.0, 0.01);
	oscAmt2Slider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	//oscAmt2Slider.setPopupDisplayEnabled(true, this);
	oscAmt2Slider.setTextValueSuffix(" Modulation");

	oscFreq2Slider.setSliderStyle(Slider::LinearBarVertical);
	oscFreq2Slider.setRange(0.0, 1.0, 0.01);
	oscFreq2Slider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	//oscFreq2Slider.setPopupDisplayEnabled(true, this);
	oscFreq2Slider.setTextValueSuffix(" Frequency");

	//add the slider to the editor
	addAndMakeVisible(&drySlider);
	addAndMakeVisible(&wetSlider);
	addAndMakeVisible(&timeSlider);
	addAndMakeVisible(&dampSlider);

	addAndMakeVisible(&feedbackSlider);
	addAndMakeVisible(&delaySlider);
	addAndMakeVisible(&oscAmtSlider);
	addAndMakeVisible(&oscFreqSlider);

	addAndMakeVisible(&feedback2Slider);
	addAndMakeVisible(&delay2Slider);
	addAndMakeVisible(&oscAmt2Slider);
	addAndMakeVisible(&oscFreq2Slider);

	//add the listener to the volume slider
	drySlider.addListener(this);
	wetSlider.addListener(this);
	timeSlider.addListener(this);
	dampSlider.addListener(this);

	feedbackSlider.addListener(this);
	delaySlider.addListener(this);
	oscAmtSlider.addListener(this);
	oscFreqSlider.addListener(this);

	feedback2Slider.addListener(this);
	delay2Slider.addListener(this);
	oscAmt2Slider.addListener(this);
	oscFreq2Slider.addListener(this);

/*
#ifdef GPP
	sleep(1000);
#else
	_sleep(1000);
#endif
*/

	//timer for reading parameters and updating the sliders.  Initialize them there as well.
	startTimer(100);
}

//add listener function for volume slider
void ReverbAudioProcessorEditor::sliderValueChanged(Slider* slider) {

	//update both the slider and the parameter with these float values
	drySliderVal =  drySlider.getValue();
	wetSliderVal =  wetSlider.getValue();
	timeSliderVal = timeSlider.getValue();
	dampSliderVal = dampSlider.getValue();
	AudioProcessorParameter* dryPp = processor.dryP;		//the setVale method is "unavailable from the AudioParameterFloat class..
	dryPp->setValue(drySliderVal);
	AudioProcessorParameter* wetPp = processor.wetP;
	wetPp->setValue(wetSliderVal);
	AudioProcessorParameter* timePp = processor.timeP;
	timePp->setValue(timeSliderVal);
	AudioProcessorParameter* dampPp = processor.dampP;
	dampPp->setValue(dampSliderVal);

	processor.feedbackVal =  feedbackSlider.getValue();
	processor.delayVal =     delaySlider.getValue();
	processor.oscAmtVal =    oscAmtSlider.getValue();
	processor.oscFreqVal =   oscFreqSlider.getValue();

	processor.feedback2Val = feedback2Slider.getValue();
	processor.delay2Val =    delay2Slider.getValue();
	processor.oscAmt2Val =   oscAmt2Slider.getValue();
	processor.oscFreq2Val =  oscFreq2Slider.getValue();

	processor.oscAmtValScaled =   50.0f * processor.oscAmtVal;				//amount in samples of modulation
	processor.oscFreqValScaled =  5.0f  * processor.oscFreqVal;				//frequency (roughly) of modulation
	processor.oscAmtVal2Scaled =  50.0f * processor.oscAmt2Val;				//amount in samples of modulation
	processor.oscFreqVal2Scaled = 5.0f  * processor.oscFreq2Val;			//frequency (roughly) of modulation
	processor.timeValScaled =     1.0f  * pow(processor.timeP->get(), 0.5f);
	processor.dampValScaled =     16000.0f  * pow(processor.dampP->get(), 2.0f);

	processor.damping[0].setFc(processor.dampValScaled);
	processor.damping[1].setFc(processor.dampValScaled);

}

ReverbAudioProcessorEditor::~ReverbAudioProcessorEditor()
{
}

//==============================================================================
void ReverbAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(Colours::white);

	g.setColour(Colours::darkgrey);
	g.setFont(15.0f);

	g.drawFittedText("Master", 30,  0, getWidth(), 30, Justification::bottom, 1);

	g.drawFittedText("Dry",  30,  30, getWidth(), 30, Justification::bottom, 1);
	g.drawFittedText("Wet",  60,  30, getWidth(), 30, Justification::bottom, 1);
	g.drawFittedText("Dec",  90,  30, getWidth(), 30, Justification::bottom, 1);
	g.drawFittedText("Damp", 120, 30, getWidth(), 30, Justification::bottom, 1);

	g.drawFittedText("Allpass1", 180, 0, getWidth(), 30, Justification::bottom, 1);

	g.drawFittedText("Fbk",  180, 30, getWidth(),  30, Justification::bottom, 1);
	g.drawFittedText("Del",  210, 30, getWidth(),  30, Justification::bottom, 1);
	g.drawFittedText("Mod",  240, 30, getWidth(),  30, Justification::bottom, 1);
	g.drawFittedText("Freq", 270, 30, getWidth(),  30, Justification::bottom, 1);

	g.drawFittedText("Allpass2", 330, 0, getWidth(), 30, Justification::bottom, 1);

	g.drawFittedText("Fbk",  330, 30, getWidth(),  30, Justification::bottom, 1);
	g.drawFittedText("Del",  360, 30, getWidth(),  30, Justification::bottom, 1);
	g.drawFittedText("Mod",  390, 30, getWidth(),  30, Justification::bottom, 1);
	g.drawFittedText("Freq", 420, 30, getWidth(),  30, Justification::bottom, 1);
}

void ReverbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	drySlider.setBounds      (30,   60, 20, getHeight() - 90);
	wetSlider.setBounds      (60,   60, 20, getHeight() - 90);
	timeSlider.setBounds     (90,   60, 20, getHeight() - 90);
	dampSlider.setBounds     (120,  60, 20, getHeight() - 90);
	
	feedbackSlider.setBounds (180,  60, 20, getHeight() - 90);
	delaySlider.setBounds    (210,  60, 20, getHeight() - 90);
	oscAmtSlider.setBounds   (240,  60, 20, getHeight() - 90);
	oscFreqSlider.setBounds  (270,  60, 20, getHeight() - 90);
	
	feedback2Slider.setBounds(330,  60, 20, getHeight() - 90);
	delay2Slider.setBounds   (360,  60, 20, getHeight() - 90);
	oscAmt2Slider.setBounds  (390,  60, 20, getHeight() - 90);
	oscFreq2Slider.setBounds (420,  60, 20, getHeight() - 90);
}




//add timerCallback so that when parameters are updated, the sliders get updated too..
void ReverbAudioProcessorEditor::timerCallback()
{

	//update both the parameter and the slider with these float values
	drySliderVal =  processor.dryP->get();
	wetSliderVal =  processor.wetP->get();
	timeSliderVal = processor.timeP->get();
	dampSliderVal = processor.dampP->get();
	drySlider.setValue(drySliderVal);
	wetSlider.setValue(wetSliderVal);
	timeSlider.setValue(timeSliderVal);
	dampSlider.setValue(dampSliderVal);

	feedbackSlider.setValue(processor.feedbackVal);
	delaySlider.setValue(processor.delayVal);
	oscAmtSlider.setValue(processor.oscAmtVal);
	oscFreqSlider.setValue(processor.oscFreqVal);

	feedback2Slider.setValue(processor.feedback2Val);
	delay2Slider.setValue(processor.delay2Val);
	oscAmt2Slider.setValue(processor.oscAmt2Val);
	oscFreq2Slider.setValue(processor.oscFreq2Val);

	processor.oscAmtValScaled = 50.0f * processor.oscAmtVal;				//amount in samples of modulation
	processor.oscFreqValScaled = 5.0f  * processor.oscFreqVal;				//frequency (roughly) of modulation
	processor.oscAmtVal2Scaled = 50.0f * processor.oscAmt2Val;				//amount in samples of modulation
	processor.oscFreqVal2Scaled = 5.0f  * processor.oscFreq2Val;			//frequency (roughly) of modulation
	processor.timeValScaled = 1.0f  * pow(processor.timeP->get(), 0.5f);
	processor.dampValScaled = 16000.0f  * pow(processor.dampP->get(), 2.0f);

	processor.damping[0].setFc(processor.dampValScaled);
	processor.damping[1].setFc(processor.dampValScaled);

}
