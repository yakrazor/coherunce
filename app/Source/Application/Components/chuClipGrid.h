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

class chuClipGrid : public Component, public ChangeListener, public TextButton::Listener
{
public:
    chuClipGrid();
    ~chuClipGrid();

    virtual void paint(Graphics& g) override;
    virtual void resized() override;

    virtual void changeListenerCallback(ChangeBroadcaster* source) override;
    virtual void buttonClicked(Button*) override;

    void addGenerator(chuGenerator* gen);

private:
    OwnedArray<chuClipButton> childControls;
    ScopedPointer<TextButton> addButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(chuClipGrid)
};


#endif  // CHUCLIPGRID_H_INCLUDED
