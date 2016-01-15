/*
  ==============================================================================

    chuGlobalControls.cpp
    Created: 15 Jan 2016 12:06:38am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "chuGlobalControls.h"
#include "chuApplication.h"

//==============================================================================
chuGlobalControls::chuGlobalControls()
{
    stopButton = new TextButton;
    stopButton->setButtonText("Stop Output");
    stopButton->setName("STOP");
    stopButton->setColour(TextButton::buttonColourId, Colours::red);
    stopButton->addListener(this);
    stopButton->setConnectedEdges(
                                  Button::ConnectedEdgeFlags::ConnectedOnLeft|Button::ConnectedEdgeFlags::ConnectedOnBottom);
    addAndMakeVisible(stopButton);

    intensitySlider = new Slider();
    intensityLabel = new Label();
    intensityLabel->setText("Intensity", dontSendNotification);
    intensitySlider->setRange(0.0, 1.0);
    intensitySlider->setValue(0.0);
    intensitySlider->setSliderStyle(Slider::LinearBar);
    intensitySlider->setName("INTENSITY");
    intensitySlider->addListener(this);
    addAndMakeVisible(intensitySlider);
    addAndMakeVisible(intensityLabel);

    enableButton = new TextButton;
    enableButton->setButtonText("Enable\nLaser");
    enableButton->setName("GO");
    enableButton->setColour(TextButton::buttonColourId, Colours::green);
    enableButton->addListener(this);
    addAndMakeVisible(enableButton);
}

chuGlobalControls::~chuGlobalControls()
{
}

void chuGlobalControls::paint (Graphics& g)
{
    g.fillAll(Colours::black);
}

void chuGlobalControls::resized()
{
    int height = getHeight();
    stopButton->setBounds(-5, height - 70, 115, 75);
    intensitySlider->setBounds(120, height - 40, 55, 30);
    intensityLabel->setBounds(120, height - 65, 55, 25);
    enableButton->setBounds(185, height - 70, 60, 60);
}

void chuGlobalControls::buttonClicked(Button* button)
{
    if (button->getName() == "STOP")
    {
        getApp()->getLaserOutputThread()->disableOutput();
    }
    else if (button->getName() == "GO")
    {
        getApp()->getLaserOutputThread()->enableOutput();
    }
}

void chuGlobalControls::sliderValueChanged(Slider* slider)
{
    if (slider && slider->getName() == "INTENSITY")
    {
        getApp()->getLaserOutputThread()->setGlobalIntensity(slider->getValue());
        return;
    }
}
