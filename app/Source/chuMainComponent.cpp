/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "chuApplication.h"
#include "chuOSCManager.h"
#include "chuGeneratorManager.h"
#include "chuClipButton.h"
#include "chuLookAndFeel.h"


class chuMainComponent : public Component, public Button::Listener, public Slider::Listener
{
public:

    ScopedPointer<TextButton> stopButton;
    ScopedPointer<Slider> intensitySlider;
    ScopedPointer<Label> intensityLabel;
    ScopedPointer<TextButton> enableButton;
    ScopedPointer<PropertyPanel> parameters;

    chuLookAndFeel customLookAndFeel;

    chuMainComponent()
    {
        LookAndFeel::setDefaultLookAndFeel(&customLookAndFeel);

        chuOSCManager::initialize(7900);
        chuGeneratorManager::initialize();

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

        int generatorCount = 0;
        for (auto& generator : chuGeneratorManager::getAllGenerators())
        {
            auto cb = new chuClipButton();
            cb->setGenerator(generator);
            cb->setBounds(0 + 120 * generatorCount, 0, 120, 110);
            addAndMakeVisible(cb);
            childControls.add(cb);

            generatorCount++;
        }

        parameters = chuGeneratorManager::getAllGenerators()[0]->createPanel();
        addAndMakeVisible(parameters);

        setSize(1100, 720);
    }

    void resized() override
    {
        int windowHeight = this->getHeight();
        int windowWidth = this->getWidth();

        stopButton->setBounds(-5, windowHeight - 70, 115, 75);
        intensitySlider->setBounds(120, windowHeight - 40, 300, 30);
        intensityLabel->setBounds(120, windowHeight - 65, 300, 25);
        enableButton->setBounds(430, windowHeight - 70, 60, 60);
        parameters->setBounds(windowWidth - 300, 0, 300, windowHeight);
    }

    ~chuMainComponent()
    {
        chuGeneratorManager::deinitialize();
        chuOSCManager::deinitialize();
    }

    void paint(Graphics& g) override
    {
        g.fillAll(Colours::black);
    }

    virtual void buttonClicked(Button* button) override
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

    virtual void sliderValueChanged (Slider* slider) override
    {
        if (slider && slider->getName() == "INTENSITY")
        {
            getApp()->getLaserOutputThread()->setGlobalIntensity(slider->getValue());
            return;
        }
    }

    OwnedArray<Component> childControls;
};

// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()    { return new chuMainComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
