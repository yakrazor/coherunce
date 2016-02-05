/*
  ==============================================================================

    chuClipButton.cpp
    Created: 8 Jan 2016 7:25:48pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "chuClipButton.h"

#include "Core/Generators/chuGenerator.h"
#include "chuGeneratorManager.h"
#include "chuApplication.h"

//==============================================================================
chuClipButton::chuClipButton()
: generator(nullptr)
{
    labelHeight = 25;
    borderWidth = 2;

    mainButton = new DrawableButton("", DrawableButton::ImageFitted);
    mainButton->addListener(this);

    labelButton = new TextButton("");
    labelButton->setConnectedEdges(TextButton::ConnectedOnTop);
    labelButton->addListener(this);
    
    addAndMakeVisible(mainButton);
    addAndMakeVisible(labelButton);
}

void chuClipButton::paint(Graphics& g)
{
    g.fillAll(Colours::black);

    auto r = getLocalBounds();
    float w = r.getWidth();
    float h = r.getHeight();

    g.setColour(Colours::darkgrey);
    g.drawLine(w, 0, w, h - labelHeight);

    if (generator && generator->isActive())
    {
        auto r = getLocalBounds();
        r.removeFromBottom(labelHeight - 1);
        r.reduce(1, 0);
        g.setColour(Colours::skyblue);
        g.fillRect(r);
        r.reduce(borderWidth, borderWidth);
        g.setColour(Colours::black);
        g.fillRect(r);
    }
}

void chuClipButton::setGenerator(chuGenerator* gen)
{
    generator = gen;
    labelButton->setButtonText(gen->getName());
}

}

void chuClipButton::setFocus(bool focused)
{
    labelButton->setToggleState(focused, dontSendNotification);
    
    if (focused)
    {
    } else {
    }
}

void chuClipButton::resized()
{
    auto r = getLocalBounds();
    auto lowerStrip = r.removeFromBottom(labelHeight);
    
    mainButton->setBounds(r);
    labelButton->setBounds(lowerStrip);
}

void chuClipButton::buttonClicked(Button* button)
{
    if (button == mainButton && generator != nullptr)
    {
        bool clipActive = !generator->isActive();
        generator->setActive(clipActive);
        if (clipActive)
        {
            getGeneratorManager()->setCurrentGenerator(generator);
        }
        repaint();
    }
    else if (button == labelButton)
    {
        getGeneratorManager()->setCurrentGenerator(generator);
    }
}