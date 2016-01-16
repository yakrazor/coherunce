/*
  ==============================================================================

    chuClipGrid.h
    Created: 15 Jan 2016 12:07:26am
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUCLIPGRID_H_INCLUDED
#define CHUCLIPGRID_H_INCLUDED

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "chuClipButton.h"

class chuClipGrid : public Component, public ChangeListener
{
public:
    chuClipGrid();
    ~chuClipGrid();

    void paint(Graphics& g);
    void resized();

    virtual void changeListenerCallback(ChangeBroadcaster* source) override;

private:
    OwnedArray<chuClipButton> childControls;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(chuClipGrid)
};


#endif  // CHUCLIPGRID_H_INCLUDED
