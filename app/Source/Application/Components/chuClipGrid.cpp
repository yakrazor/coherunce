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
    int generatorCount = 0;
    for (auto& generator : chuGeneratorManager::getAllGenerators())
    {
        auto cb = new chuClipButton();
        cb->setGenerator(generator);
        cb->setBounds(0 + 120 * generatorCount, 0, 120, 110);
        addAndMakeVisible(cb);
        childControls.add(cb);

        generatorCount++;
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
