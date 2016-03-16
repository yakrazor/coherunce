/*
  ==============================================================================

    chuClipGrid.cpp
    Created: 15 Jan 2016 12:07:26am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "chuClipGrid.h"
#include "chuGeneratorManager.h"
#include "chuClipButton.h"

//==============================================================================
chuClipGrid::chuClipGrid()
{
    auto manager = getGeneratorManager();
    if (!manager)
    {
        return;
    }

    manager->addChangeListener(this);

    auto& generators = manager->getAllGenerators();
    int cols = 5;
    int rows = 5;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            auto cb = new chuClipButton();
            int index = i * cols + j;
            if (index < generators.size())
            {
                cb->setGenerator(generators[index]);
            }
            cb->setBounds(120 * j, 110 * i, 120, 110);
            addAndMakeVisible(cb);
            childControls.add(cb);
        }
    }
}

chuClipGrid::~chuClipGrid()
{
}

void chuClipGrid::paint(Graphics& g)
{
    g.fillAll(Colours::black);
}

void chuClipGrid::resized()
{

}

void chuClipGrid::changeListenerCallback(ChangeBroadcaster* source)
{
    chuGeneratorManager* mgr = dynamic_cast<chuGeneratorManager*>(source);
    if (mgr)
    {
        auto currentGen = mgr->getCurrentGenerator();
        for (auto gridButton : childControls)
        {
            gridButton->setFocus(currentGen != nullptr && gridButton->getGenerator() == currentGen);
        }
    }
}
