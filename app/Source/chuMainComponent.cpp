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

class GeneratorParameterSlider : public Slider
{
public:
    GeneratorParameterSlider(GeneratorParameterFloat* pParam) : param(pParam)
    {
        setRange(param->minValue, param->maxValue);
        setValue(param->value);
    }
    void updateParam() { param->value = (float)getValue(); }
private:
    GeneratorParameterFloat* param;
};

class chuMainComponent : public Component, public Button::Listener, public Slider::Listener
{
public:
    //==============================================================================
    chuMainComponent()
    {
        setSize(1100, 720);

        chuOSCManager::initialize(7900);
        chuGeneratorManager::initialize();

        int generatorCount = 0;
        for (auto& generator : chuGeneratorManager::getAllGenerators())
        {
            std::vector<GeneratorParameterFloat*> params;
            generator->getParams(params);

            auto button = new GeneratorButton(generatorCount);
            generatorControls.add(button);

            String description = generator->getName() + " " + String(generatorCount + 1);
            button->setButtonText(description);

            button->setToggleState(generator->isActive(), dontSendNotification);
            button->setClickingTogglesState(true);
            button->setBounds(10 + 160 * generatorCount, 10, 150, 60);
            button->addListener(this);
            addAndMakeVisible(button);

            int paramCount = 0;
            for (auto& param : params)
            {
                if (!param->userVisible)
                    continue;

                auto slider = new GeneratorParameterSlider(param);
                slider->setSliderStyle(Slider::LinearBar);
                auto label = new Label();
                label->setText(param->name, dontSendNotification);
                label->setBounds(10 + 160 * generatorCount, 80 + paramCount * 45, 150, 15);
                slider->setBounds(10 + 160 * generatorCount, 95 + paramCount * 45, 150, 20);

                slider->addListener(this);

                generatorControls.add(label);
                generatorControls.add(slider);
                addAndMakeVisible(label);
                addAndMakeVisible(slider);

                paramCount++;
            }


            generatorCount++;
        }
    }

    virtual void buttonClicked(Button* button) override
    {

    }

    virtual void buttonStateChanged(Button* button) override
    {
        auto gb = static_cast<GeneratorButton*>(button);
        if (gb)
        {
            auto& generators = chuGeneratorManager::getAllGenerators();
            if (gb->generatorIndex >= 0 && gb->generatorIndex < generators.size())
            {
                generators[gb->generatorIndex]->setActive(button->getToggleState());
            }
        }
    }

    virtual void sliderValueChanged (Slider* slider) override
    {
        GeneratorParameterSlider* gps = static_cast<GeneratorParameterSlider*>(slider);
        if (gps)
        {
            gps->updateParam();
        }
    }

    OwnedArray<Component> generatorControls;
};

// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()    { return new chuMainComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
