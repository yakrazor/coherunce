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
    chuParameterInt(const String& _name, int _min, int _max, int _defaultValue, const chuParameterOptions& _options = chuParameterOptions::Default);
    virtual ~chuParameterInt() {}

    virtual PropertyComponent* createComponent() override;
    virtual void oscMessageReceived(const OSCMessage &message) override;

    int getMinValue() const { return minValue.load(); }
    int getMaxValue() const { return maxValue.load(); }
    int getValue() const { return value.load(); }
    void setValue(int newValue) { value.store(newValue); }

private:
    std::atomic<int> minValue;
    std::atomic<int> maxValue;
    std::atomic<int> value;
};


#endif  // CHUPARAMETERINT_H_INCLUDED
