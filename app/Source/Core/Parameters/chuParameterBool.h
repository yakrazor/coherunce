/*
  ==============================================================================

    chuParameterBool.h
    Created: 16 Jan 2016 11:30:36pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUPARAMETERBOOL_H_INCLUDED
#define CHUPARAMETERBOOL_H_INCLUDED

#include "chuParameterBase.h"

class chuParameterBool : public chuParameter {
public:
    chuParameterBool(const String& _name, bool _defaultValue, const chuParameterOptions& _options = chuParameterOptions::Default);
    virtual ~chuParameterBool() {}

    virtual PropertyComponent* createComponent() override;
    virtual void oscMessageReceived(const OSCMessage &message) override;

    bool getValue() const { return value.load(); }
    void setValue(bool newValue) { value.store(newValue); }

private:
    std::atomic<bool> value;
};


#endif  // CHUPARAMETERBOOL_H_INCLUDED
