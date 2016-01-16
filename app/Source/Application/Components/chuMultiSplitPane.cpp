/*
  ==============================================================================

    chuThreePaneSplitter.cpp
    Created: 11 Jan 2016 4:24:38am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "chuMultiSplitPane.h"

#define SPLITTER_WIDTH = 8;

chuMultiSplitPane::chuMultiSplitPane()
: flexComponentIndex(-1), splitterWidth(5)
{
}

chuMultiSplitPane::~chuMultiSplitPane()
{
}

void chuMultiSplitPane::paint (Graphics& g)
{
    g.fillAll (Colours::white);   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
    g.drawText ("chuThreePaneSplitter", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void chuMultiSplitPane::resized()
{
    int currentX = 0;
    int currentWidth = 0;
    int totalLeft = 0;
    int totalRight = 0;

    for (int i = 0; i < children.size(); i++)
    {
        if (i < flexComponentIndex)
        {
            currentWidth = splitters[i]->getWidth();
            totalLeft += currentWidth + splitterWidth;

            children[i]->setBounds(currentX, 0, currentWidth, getHeight());
            splitters[i]->setBounds(currentX + currentWidth, 0, splitterWidth, getHeight());
            currentX = totalLeft;
        }
        else if (i == flexComponentIndex)
        {
            currentX = 0;
            continue;
        }
        else if (i > flexComponentIndex)
        {
            currentWidth = splitters[i]->getWidth();
            totalRight += currentWidth + splitterWidth;

            children[i]->setBounds(getWidth() - currentX - currentWidth, 0, currentWidth, getHeight());
            splitters[i]->setBounds(getWidth() - currentX - currentWidth - splitterWidth, 0, splitterWidth, getHeight());
            currentX = totalRight;
        }

    }

    int flexWidth = jmax(0, getWidth() - totalLeft - totalRight);
    children[flexComponentIndex]->setVisible(flexWidth != 0);
    children[flexComponentIndex]->setBounds(totalLeft, 0, flexWidth, getHeight());
}

void chuMultiSplitPane::addPane(Component* pane, int minWidth, int maxWidth, int startWidth, bool expandable)
{
    children.add(pane);
    addAndMakeVisible(pane);

    auto splitter = new SplitterBar(minWidth, maxWidth, startWidth);
    splitter->setDirection(flexComponentIndex >= 0 ? -1 : 1);
    addAndMakeVisible(splitter);
    splitters.add(splitter);

    if (expandable == true && flexComponentIndex == -1)
    {
        flexComponentIndex = children.size() - 1;
    }
}

chuMultiSplitPane::SplitterBar::SplitterBar(int minWidth, int maxWidth, int startWidth)
: minWidth(minWidth), maxWidth(maxWidth), width(startWidth)
{
    setMouseCursor(MouseCursor(MouseCursor::LeftRightResizeCursor));
}

chuMultiSplitPane::SplitterBar::~SplitterBar()
{
}

void chuMultiSplitPane::SplitterBar::paint (Graphics& g)
{
    g.fillAll(Colours::black);
    g.setColour(Colours::darkgrey);
    g.drawLine(getLocalBounds().getCentreX(), 0, getLocalBounds().getCentreX(), getHeight());
}

void chuMultiSplitPane::SplitterBar::resized()
{
    
}


void chuMultiSplitPane::SplitterBar::mouseDown(const MouseEvent&)
{
    startMouseDragOffset = width;
}

void chuMultiSplitPane::SplitterBar::mouseDrag(const MouseEvent& e)
{
    int dragDistance = e.getDistanceFromDragStartX();

    width = jmin(maxWidth, jmax(minWidth, startMouseDragOffset + direction * dragDistance));
    getParentComponent()->resized();
}

