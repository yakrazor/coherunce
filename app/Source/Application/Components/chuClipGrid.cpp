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
            cb->setBounds(120 * j, 110 * i, 120, 110);
            addAndMakeVisible(cb);
            childControls.add(cb);

            int index = i * cols + j;
            if (index < generators.size())
            {
                cb->setGenerator(generators[index]);
            }
            else if (index == generators.size())
            {
                addButton = new TextButton();
                addButton->setBounds(cb->getX() + 10, cb->getY() + 10, 25, 22);
                addButton->setButtonText(" + ");
                addButton->setTooltip("Add Generator");
                addButton->setTriggeredOnMouseDown(true);
                addButton->addListener(this);
                addAndMakeVisible(addButton);
            }

        }
    }
}

chuClipGrid::~chuClipGrid()
{
    auto manager = getGeneratorManager();
    if (manager)
    {
        manager->removeChangeListener(this);
    }
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

void chuClipGrid::addGenerator(chuGenerator* newGen)
{
    auto manager = getGeneratorManager();

    int lastIndex = manager->getAllGenerators().size();
    if (lastIndex < childControls.size())
    {
        childControls[lastIndex]->setGenerator(newGen);
        getApp()->getCurrentProject()->addGenerator(newGen);
        int x = 120 * ((lastIndex + 1) % 5) + 10;
        int y = 110 * ((lastIndex + 1) / 5) + 10;

        if (lastIndex + 1 < childControls.size())
        {
            addButton->setTopLeftPosition(x, y);
            addButton->toFront(false);
        }
        else
        {
            addButton->setVisible(false);
        }
    }
}

void addGeneratorFromMenu(int result, chuClipGrid* grid)
{
    // TODO: replace this with a proper factory
    chuGenerator* newGen = nullptr;
    switch (result)
    {
        case 1: newGen = new chuGenPolygonPinwheel(); break;
        case 2: newGen = new chuGenFivePoints(); break;
        case 3: newGen = new chuGen16Step(); break;
        case 4: newGen = new chuGenJavascript(); break;
    }
    grid->addGenerator(newGen);
}

void chuClipGrid::buttonClicked(Button* button)
{
    if (button == addButton)
    {
        PopupMenu m;
        m.addItem(1, "PolygonPinwheel");
        m.addItem(2, "FivePoints");
        m.addItem(3, "16Step");
        m.addItem(4, "CustomJavascript");
        m.showMenuAsync(PopupMenu::Options().withTargetComponent(addButton),
                        ModalCallbackFunction::create(addGeneratorFromMenu, this));
    }
}

