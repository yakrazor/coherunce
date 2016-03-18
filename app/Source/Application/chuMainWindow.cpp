/*
  ==============================================================================

    chuMainWindow.cpp
    Created: 25 Dec 2015 5:13:36pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuMainWindow.h"
#include "chuLookAndFeel.h"
#include "chuApplication.h"

#include "chuMultiSplitPane.h"
#include "chuGlobalControls.h"
#include "chuClipGrid.h"
#include "chuInspector.h"
#include "chuGeneratorManager.h"


chuMainWindow::chuMainWindow(String name)
: DocumentWindow(name, Colours::lightgrey, DocumentWindow::allButtons)
{
    setUsingNativeTitleBar(true);

    customLookAndFeel = new chuLookAndFeel();
    LookAndFeel::setDefaultLookAndFeel(customLookAndFeel);

    addKeyListener(getApp()->getApplicationCommandManager().getKeyMappings());

    clipGrid = new chuClipGrid();

    auto splitPane = new chuMultiSplitPane();
    splitPane->addPane(new chuGlobalControls(), 250, 300, 250);
    splitPane->addPane(clipGrid, 100, 500, 200, true);
    splitPane->addPane(new chuInspector(getGeneratorManager()), 50, 400, 300);
    splitPane->setBounds(getBounds());
    setContentOwned(splitPane, true);

    setResizable(true, true);
    setResizeLimits(750, 400, 250000, 250000);
    centreWithSize(1200, 700);
    setVisible(true);
}

chuMainWindow::~chuMainWindow()
{
}

void chuMainWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}