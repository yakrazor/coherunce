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
    chuParameterString(const String& name, const String& str, const chuParameterOptions& options = chuParameterOptions::Default);
    virtual ~chuParameterString() {}

    virtual void deserialize(ValueTree saved) override;
    virtual void oscMessageReceived(const OSCMessage &message) override;
    virtual PropertyComponent* createComponent() override;

    const String getValue() const;
    void setValue(const String& str);
};


#endif  // CHUPARAMETERSTRING_H_INCLUDED
