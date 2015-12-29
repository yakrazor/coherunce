/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "chuApplication.h"
#include "chuLaserCalibrationComponent.h"

class chuMainComponent : public OpenGLAppComponent
{
public:
    //==============================================================================
    chuMainComponent()
    {
        setSize(1100, 720);
        calibrationComponent = new chuLaserCalibrationComponent();
        addChildAndSetID(calibrationComponent, "calibration");
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
    ScopedPointer<Component> calibrationComponent;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (chuMainComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()    { return new chuMainComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
