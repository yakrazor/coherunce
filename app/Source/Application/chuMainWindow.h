/*
  ==============================================================================

    chuMainWindow.h
    Created: 25 Dec 2015 5:13:36pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUMAINWINDOW_H_INCLUDED
#define CHUMAINWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "chuClipGrid.h"

class chuMainWindow : public DocumentWindow
{
public:
    chuMainWindow(String name);
    ~chuMainWindow();

    void closeButtonPressed() override;

    static chuMainWindow* getMainWindow();

    chuClipGrid* getClipGrid() { return clipGrid; }

private:
    ScopedPointer<LookAndFeel> customLookAndFeel;
    chuClipGrid* clipGrid;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(chuMainWindow)
};


#endif  // CHUMAINWINDOW_H_INCLUDED
