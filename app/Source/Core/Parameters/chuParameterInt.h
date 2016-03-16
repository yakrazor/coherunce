/*
  ==============================================================================

    chuParameterInt.h
    Created: 16 Jan 2016 11:30:19pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUPARAMETERINT_H_INCLUDED
#define CHUPARAMETERINT_H_INCLUDED

#include "chuParameterBase.h"

class chuParameterInt : public chuParameter {
public:
    chuParameterInt(const String& name, int min, int max, int defaultValue, const chuParameterOptions& _options = chuParameterOptions::Default);
    virtual ~chuParameterInt() {}

    virtual void deserialize(ValueTree saved) override;
    virtual void oscMessageReceived(const OSCMessage &message) override;
    virtual PropertyComponent* createComponent() override;

    int getMinValue() const;
    int getMaxValue() const;
    int getValue() const;

    void setMinValue(int newMin);
    void setMaxValue(int newMax);
    void setValue(int newValue);
};


#endif  // CHUPARAMETERINT_H_INCLUDED
