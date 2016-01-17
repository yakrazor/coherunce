/*
  ==============================================================================

    chuClipButton.cpp
    Created: 8 Jan 2016 7:25:48pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "chuClipButton.h"

#include "chuGenerator.h"
#include "chuGeneratorManager.h"

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

chuClipButton::~chuClipButton()
{
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

void drawGeneratorPreview(chuGenerator* generator, DrawableComposite* preview)
{
    if (!generator || !preview)
    {
        return;
    }

    auto items = generator->getPatterns(0.0);

    auto border = new DrawablePath();
    Path borderPath;
    borderPath.addRectangle(-100, -100, 200, 200);
    border->setStrokeFill(Colours::black);
    border->setStrokeThickness(1.0);
    border->setPath(borderPath);
    preview->addAndMakeVisible(border);

    for (auto& item : items)
    {
        if (item.type == PatternType::RegularPolygon)
        {
            Path path;
            path.addPolygon(Point<float>(item.origin.x * 100, item.origin.y * 100),
                            item.sides,
                            item.radius * 100,
                            item.rotation);

            auto dp = new DrawablePath();
            dp->setStrokeFill(Colour(item.red >> 8, item.green >> 8, item.blue >> 8));
            dp->setFill(Colours::transparentBlack);
            dp->setStrokeThickness(2.0f);
            dp->setPath(path);
            
            preview->addAndMakeVisible(dp);
        }
        else if (item.type == PatternType::Polyline)
        {
            auto& vertices = item.polyline.vertices;
            for (int i = 1; i < vertices.size(); i++)
            {
                Path path;
                path.addLineSegment(
                    Line<float>(
                        vertices[i-1].x * 100, vertices[i-1].y * -100,
                        vertices[i].x * 100, vertices[i].y * -100),
                    1
                );

                auto dp = new DrawablePath();
                dp->setStrokeFill(item.polyline.colours[i]);
                dp->setFill(Colours::transparentBlack);
                dp->setStrokeThickness(2.0f);
                dp->setPath(path);

                preview->addAndMakeVisible(dp);
            }
        }
    }
}

void chuClipButton::setGenerator(chuGenerator* gen)
{
    generator = gen;
    labelButton->setButtonText(gen->getName());
    updatePreview();
}

void chuClipButton::updatePreview()
{
    preview = new DrawableComposite();
    preview->setBoundingBox(RelativeParallelogram(Rectangle<float>(-100.0, 100.0, 100.0, -100.0)));
    drawGeneratorPreview(generator, preview);
    mainButton->setImages(preview);
}

void chuClipButton::setFocus(bool focused)
{
    labelButton->setToggleState(focused, dontSendNotification);
    
    // TODO: need to update preview whenever properties change; for now, update on focus as a workaround
    updatePreview();
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