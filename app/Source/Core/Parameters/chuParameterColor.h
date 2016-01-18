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
    chuParameterColor(const String& _name, const Color& _color, const chuParameterOptions& _options = chuParameterOptions::Default);
    virtual ~chuParameterColor() {}

    virtual PropertyComponent* createComponent() override;
    virtual void oscMessageReceived(const OSCMessage &message) override;

    Color getValue() const { return Color(value.load()); }
    void setValue(const Color& c) { value.store(c.getARGB()); }

private:
    std::atomic<uint32> value;
};


#endif  // CHUPARAMETERCOLOR_H_INCLUDED
