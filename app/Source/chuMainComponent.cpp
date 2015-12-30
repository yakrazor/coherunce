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

#include "chuGeneratorManager.h"

class GeneratorButton : public TextButton
{
public:
    GeneratorButton(int index) : generatorIndex(index) {

    }
    int generatorIndex;
};

class chuMainComponent : public Component, public Button::Listener
{
public:
    //==============================================================================
    chuMainComponent()
    {
        setSize(1100, 720);

        int generatorCount = 0;
        for (auto& generator : chuGeneratorManager::getAllGenerators())
        {
            std::vector<GeneratorParameterFloat*> params;
            generator->getParams(params);

            auto button = new GeneratorButton(generatorCount);

            String description = generator->getName();
            if (params.size() > 0) {
                description += "\n";
            }
            for (auto& param : params)
            {
                description += " ";
                description += param->name;
                description += "=";
                description += String(param->value);
            }
            button->setButtonText(description);

            button->setToggleState(generator->isActive(), dontSendNotification);
            button->setClickingTogglesState(true);
            button->setBounds(10, 10 + 110 * generatorCount, 200, 100);
            button->addListener(this);
            addAndMakeVisible(button);

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

    OwnedArray<Component> generatorButtons;
};

// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()    { return new chuMainComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
