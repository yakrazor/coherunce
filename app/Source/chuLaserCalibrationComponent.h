/*
  ==============================================================================

    chuLaserCalibrationComponent.h
    Created: 26 Dec 2015 8:19:13pm
    Author:  Matthew Stone

  ==============================================================================
*/

#ifndef CHULASERCALIBRATIONCOMPONENT_H_INCLUDED
#define CHULASERCALIBRATIONCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class chuLaserCalibrationComponent    : public Component
{
public:
    chuLaserCalibrationComponent();
    ~chuLaserCalibrationComponent();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (chuLaserCalibrationComponent)
};


#endif  // CHULASERCALIBRATIONCOMPONENT_H_INCLUDED
