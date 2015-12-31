/*
  ==============================================================================

    chuMainWindow.cpp
    Created: 25 Dec 2015 5:13:36pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuApplication.h"
#include "chuMainWindow.h"

Component* createMainContentComponent();

chuMainWindow::chuMainWindow(String name)
: DocumentWindow(name, Colours::lightgrey, DocumentWindow::allButtons)
{
    setUsingNativeTitleBar(true);
    setContentOwned(createMainContentComponent(), true);
    setResizable(true, true);
    setResizeLimits(750, 500, 250000, 250000);

    addKeyListener(getApp()->getApplicationCommandManager().getKeyMappings());

    centreWithSize(getWidth(), getHeight());
    setVisible(true);
}

chuMainWindow::~chuMainWindow()
{
}

void chuMainWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}