/*
  ==============================================================================

    chuGeneratorPreview.h
    Created: 4 Feb 2016 12:51:07pm
    Author:  Matthew Stone

  ==============================================================================
*/

#ifndef CHUGENERATORPREVIEW_H_INCLUDED
#define CHUGENERATORPREVIEW_H_INCLUDED

#include "Core/Generators/chuGenerator.h"
#include "chuGeneratorManager.h"
#include "chuApplication.h"

class chuGeneratorPreview : public Timer, public Component, public ChangeBroadcaster {
public:
    // pub
    chuGeneratorPreview(chuGenerator* gen);
    ~chuGeneratorPreview();
    
    void setGenerator(chuGenerator* gen);
    void startPreviewUpdate();
    void stopPreviewUpdate();
    void drawGeneratorPreview();
    DrawableComposite* getPreviewBuffer();

    virtual void timerCallback() override;
    
    

private:
    // priv
    chuGenerator* generator;
    const int previewHz = 60;
    ScopedPointer<DrawableComposite> previewBuffer;
    const float resolution = 200.0;

};


#endif  // CHUGENERATORPREVIEW_H_INCLUDED
