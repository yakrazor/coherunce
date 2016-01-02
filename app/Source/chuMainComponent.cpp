/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "chuApplication.h"

/*
class chuMainComponent : public OpenGLAppComponent
{
public:
    //==============================================================================
    chuMainComponent()
    {
        setSize(1100, 720);
    }

    ~chuMainComponent()
    {
        shutdownOpenGL();
    }

    void initialise() override
    {
    }

    void shutdown() override
    {
    }

    void render() override
    {
        OpenGLHelpers::clear (Colours::black);

    }

    void paint (Graphics& g) override
    {
        // You can add your component specific drawing code here!
        // This will draw over the top of the openGL background.
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
    }


private:
    //==============================================================================

    // private member variables



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (chuMainComponent)
};
*/

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

            int paramCount = 0;
            for (auto& param : params)
            {
                if (!param->options.isUserVisible)
                    continue;

                auto slider = param->createComponent();
                auto label = new Label();
                label->setText(param->name, dontSendNotification);
                label->setBounds(10 + 160 * generatorCount, 80 + paramCount * 45, 150, 15);
                slider->setBounds(10 + 160 * generatorCount, 95 + paramCount * 45, 150, 20);

                childControls.add(label);
                childControls.add(slider);
                addAndMakeVisible(label);
                addAndMakeVisible(slider);

                paramCount++;
            }


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
            getApp()->getLaserOutputThread()->setGlobalIntensity(slider->getValue());
            return;
        }
    }

    OwnedArray<Component> childControls;
};

// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()    { return new chuMainComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
