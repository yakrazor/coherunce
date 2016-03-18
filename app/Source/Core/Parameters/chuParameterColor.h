/*
  ==============================================================================

    chuParameterColor.h
    Created: 16 Jan 2016 11:30:50pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUPARAMETERCOLOR_H_INCLUDED
#define CHUPARAMETERCOLOR_H_INCLUDED

#include "chuParameterBase.h"

typedef Colour Color;
typedef Colours Colors;

class chuParameterColor : public chuParameter {
public:
    chuParameterColor(const String& name, const Color& color, const chuParameterOptions& options = chuParameterOptions::Default);
    virtual ~chuParameterColor() {}

    virtual void deserialize(ValueTree saved) override;
    virtual void oscMessageReceived(const OSCMessage &message) override;
    virtual PropertyComponent* createComponent() override;

    Color getValue() const;
    void setValue(const Color& c);
    void setHue(float hue);
};


#endif  // CHUPARAMETERCOLOR_H_INCLUDED
