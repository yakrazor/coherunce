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

    virtual PropertyComponent* createComponent() override;
    virtual void oscMessageReceived(const OSCMessage &message) override;

    float getMinValue() const { return minValue.load(); }
    float getMaxValue() const { return maxValue.load(); }
    float getValue() const { return value.load(); }
    void setValue(float newValue) { value.store(newValue); }

private:
    std::atomic<float> minValue;
    std::atomic<float> maxValue;
    std::atomic<float> value;
};



#endif  // CHUPARAMETERFLOAT_H_INCLUDED
