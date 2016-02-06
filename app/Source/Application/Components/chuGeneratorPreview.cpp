/*
  ==============================================================================

    chuGeneratorPreview.cpp
    Created: 4 Feb 2016 12:51:07pm
    Author:  Matthew Stone

  ==============================================================================
*/

#include "chuGeneratorPreview.h"

chuGeneratorPreview::chuGeneratorPreview(chuGenerator* gen) {
    
    setGenerator(gen);
}

chuGeneratorPreview::~chuGeneratorPreview() {
    stopTimer();
}

void chuGeneratorPreview::setGenerator(chuGenerator *gen) {
    generator = gen;
    drawGeneratorPreview();
}

void chuGeneratorPreview::startPreviewUpdate() {
    startTimerHz(previewHz);
}

void chuGeneratorPreview::stopPreviewUpdate() {
    stopTimer();
}

void chuGeneratorPreview::timerCallback() {
    drawGeneratorPreview();
}

ScopedPointer<Drawable> chuGeneratorPreview::getPreviewBuffer() {
    if (!previewBuffer) {
        return nullptr;
    }
    return previewBuffer->createCopy();
}

void chuGeneratorPreview::drawGeneratorPreview()
{
    if (!generator) {
        return;
    }
    previewBuffer = new DrawableComposite();
    previewBuffer->setBoundingBox(RelativeParallelogram(Rectangle<float>(-resolution, resolution, resolution, -resolution)));
    
    auto items = generator->getPatterns(getApp()->getFrameTimer()->getBarClock());
    
    auto border = new DrawablePath();
    Path borderPath;
    borderPath.addRectangle(-resolution, -resolution, resolution * 2, resolution * 2);
    border->setStrokeFill(Colours::black);
    border->setStrokeThickness(1.0);
    border->setPath(borderPath);
    previewBuffer->addAndMakeVisible(border);
    
    for (auto& item : items)
    {
        if (item.type == PatternType::RegularPolygon)
        {
            Path path;
            path.addPolygon(Point<float>(item.origin.x * resolution, item.origin.y * resolution),
                            item.sides,
                            item.radius * resolution,
                            item.rotation * float_Pi/180.0);
            
            auto dp = new DrawablePath();
            dp->setStrokeFill(Colour(item.red >> 8, item.green >> 8, item.blue >> 8));
            dp->setFill(Colours::transparentBlack);
            dp->setStrokeThickness(2.0f);
            dp->setPath(path);
            
            previewBuffer->addAndMakeVisible(dp);
        }
        else if (item.type == PatternType::Polyline)
        {
            auto& vertices = item.polyline.vertices;
            for (int i = 1; i < vertices.size(); i++)
            {
                Path path;
                path.addLineSegment(
                    Line<float>(
                        vertices[i-1].x * resolution, vertices[i-1].y * -resolution,
                        vertices[i].x * resolution, vertices[i].y * -resolution),
                        1
                );
                
                auto dp = new DrawablePath();
                dp->setStrokeFill(item.polyline.colours[i]);
                dp->setFill(Colours::transparentBlack);
                dp->setStrokeThickness(2.0f);
                dp->setPath(path);
                
                previewBuffer->addAndMakeVisible(dp);
            }
        }
    }
    previewBuffer->setTransformToFit(getLocalBounds().toFloat(), RectanglePlacement::stretchToFit);
    addAndMakeVisible(previewBuffer);
    sendChangeMessage();

}