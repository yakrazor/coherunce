/*
  ==============================================================================

    chuParameterFloat.h
    Created: 16 Jan 2016 11:30:13pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUPARAMETERFLOAT_H_INCLUDED
#define CHUPARAMETERFLOAT_H_INCLUDED

#include "chuParameterBase.h"

class chuParameterFloat : public chuParameter {
public:
    chuParameterFloat(const String& _name, float _min, float _max, float _defaultValue, const chuParameterOptions& _options = chuParameterOptions::Default);
    virtual ~chuParameterFloat() {}

    virtual void deserialize(ValueTree saved) override;
    virtual void oscMessageReceived(const OSCMessage &message) override;
    virtual PropertyComponent* createComponent() override;

    float getMinValue() const;
    float getMaxValue() const;
    float getValue() const;

    void setMinValue(float newMin);
    void setMaxValue(float newMax);
    void setValue(float newValue);
};



#endif  // CHUPARAMETERFLOAT_H_INCLUDED
