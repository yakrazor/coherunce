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

class GeneratorButton : public TextButton
{
public:
    GeneratorButton(int index) : generatorIndex(index) {

    }
    int generatorIndex;
};


class chuMainComponent : public Component, public Button::Listener, public Slider::Listener
{
public:

    ScopedPointer<TextButton> stopButton;
    ScopedPointer<Slider> intensitySlider;
    ScopedPointer<Label> intensityLabel;
    ScopedPointer<TextButton> enableButton;

    chuMainComponent()
    {
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
            std::vector<chuParameter*> params;
            generator->getParamList(params);

            auto button = new GeneratorButton(generatorCount);
            childControls.add(button);

            String description = generator->getName() + " " + String(generatorCount + 1);
            button->setButtonText(description);

            button->setToggleState(generator->isActive(), dontSendNotification);
            button->setBounds(10 + 160 * generatorCount, 10, 150, 60);
            button->addListener(this);
            addAndMakeVisible(button);

            auto panel = generator->createPanel();
            childControls.add(panel);
            panel->setBounds(10 + 160 * generatorCount, 79, 150, 500);
            addAndMakeVisible(panel);

            generatorCount++;
        }

        setSize(1100, 720);
    }

    void resized() override
    {
        int windowHeight = this->getHeight();
        stopButton->setBounds(-5, windowHeight - 70, 115, 75);
        intensitySlider->setBounds(120, windowHeight - 40, 300, 30);
        intensityLabel->setBounds(120, windowHeight - 65, 300, 25);
        enableButton->setBounds(430, windowHeight - 70, 60, 60);
    }

    ~chuMainComponent()
    {
        chuGeneratorManager::deinitialize();
        chuOSCManager::deinitialize();
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

        GeneratorButton* gb = dynamic_cast<GeneratorButton*>(button);
        if (gb)
        {
            auto& generators = chuGeneratorManager::getAllGenerators();
            if (gb->generatorIndex >= 0 && gb->generatorIndex < generators.size())
            {
                bool genState = generators[gb->generatorIndex]->isActive();
                generators[gb->generatorIndex]->setActive(!genState);
                gb->setToggleState(!genState, dontSendNotification);
            }
        }
    }

    virtual void sliderValueChanged (Slider* slider) override
    {
        if (slider && slider->getName() == "INTENSITY")
        {
            getApp()->getLaserOutputThread()->getLaserConfig().globalIntensity.setValue(slider->getValue());
            return;
        }
    }

    OwnedArray<Component> childControls;
};

// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()    { return new chuMainComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
