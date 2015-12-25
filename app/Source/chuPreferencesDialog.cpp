/*
  ==============================================================================

    SettingsWindow.cpp
    Created: 24 Dec 2015 10:54:15pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "chuPreferencesDialog.h"
#include "chuPreferencesPageAudio.h"

//==============================================================================
chuPreferencesDialog::chuPreferencesDialog()
: DocumentWindow("Preferences", Colours::lightgrey, DocumentWindow::closeButton)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    auto audioPage = new chuPreferencesPageAudio();
    audioPage->setBounds(0, 0, 400, 600);

    setUsingNativeTitleBar(true);
    setContentOwned(audioPage, true);
    setResizable(false, false);

    addKeyListener(getApp()->getApplicationCommandManager().getKeyMappings());

    centreWithSize(getWidth(), getHeight());
}

chuPreferencesDialog::~chuPreferencesDialog()
{
    deleteAllChildren();
}

void chuPreferencesDialog::paint(Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(Colours::white);   // clear the background

    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(Colours::lightblue);
    g.setFont(14.0f);
    g.drawText("SettingsWindow", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void chuPreferencesDialog::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}

void chuPreferencesDialog::closeButtonPressed()
{
    setVisible(false);
}