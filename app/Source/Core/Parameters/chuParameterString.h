/*
  ==============================================================================

    chuParameterString.h
    Created: 16 Jan 2016 11:30:56pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUPARAMETERSTRING_H_INCLUDED
#define CHUPARAMETERSTRING_H_INCLUDED

#include "chuParameterBase.h"


class chuParameterString : public chuParameter {
public:
    chuParameterString(const String& _name, const String& str, const chuParameterOptions& _options = chuParameterOptions::Default);
    virtual ~chuParameterString() {}

    virtual PropertyComponent* createComponent() override;
    virtual void oscMessageReceived(const OSCMessage &message) override;

    const String& getValue() const { return value; }
    void setValue(const String& str) { value = str; }

private:
    String value;
};


#endif  // CHUPARAMETERSTRING_H_INCLUDED
