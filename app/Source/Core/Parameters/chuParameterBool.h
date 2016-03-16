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
    chuParameterBool(const String& name, bool defaultValue, const chuParameterOptions& options = chuParameterOptions::Default);
    virtual ~chuParameterBool() {}

    virtual void deserialize(ValueTree saved) override;
    virtual void oscMessageReceived(const OSCMessage &message) override;
    virtual PropertyComponent* createComponent() override;

    bool getValue() const;
    void setValue(bool newValue);
};


#endif  // CHUPARAMETERBOOL_H_INCLUDED
