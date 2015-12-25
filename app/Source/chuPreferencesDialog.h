/*
  ==============================================================================

    chuPreferencesDialog.h
    Created: 24 Dec 2015 10:54:15pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef SETTINGSWINDOW_H_INCLUDED
#define SETTINGSWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class chuPreferencesDialog : public DocumentWindow
{
public:
    chuPreferencesDialog();
    ~chuPreferencesDialog();

    void paint (Graphics&);
    void resized();

    void closeButtonPressed() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(chuPreferencesDialog)
};


#endif  // SETTINGSWINDOW_H_INCLUDED