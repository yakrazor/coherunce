/*
  ==============================================================================

    chuMenuBar.h
    Created: 25 Dec 2015 5:14:08pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUMENUBAR_H_INCLUDED
#define CHUMENUBAR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class chuMenuBar : public MenuBarModel
{
public:
    chuMenuBar();
    void initialize();

    virtual StringArray getMenuBarNames() override;
    virtual PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName);
    virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex);

    ~chuMenuBar();

private:
    ScopedPointer<PopupMenu> appleItems;
};


#endif  // CHUMENUBAR_H_INCLUDED
