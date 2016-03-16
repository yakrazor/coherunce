/*
  ==============================================================================

    chuParameterBase.h
    Created: 2 Jan 2016 11:47:13am
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUPARAMETER_H_INCLUDED
#define CHUPARAMETER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


class chuParameterOptions
{
public:
    chuParameterOptions() : isUserVisible(true) {}
    bool isUserVisible;

    static chuParameterOptions Default;
};

class chuParameter : public OSCReceiver::ListenerWithOSCAddress<OSCReceiver::RealtimeCallback> {
public:
    chuParameter(const String& _name, const chuParameterOptions& _options = chuParameterOptions::Default);
    virtual ~chuParameter() {}

    // Parameter subclasses must override these two methods:
    virtual PropertyComponent* createComponent() = 0;
    virtual void oscMessageReceived(const OSCMessage &message) = 0;

    const String& getName() { return name; }
    const chuParameterOptions& getOptions() { return options; }

private:
    String name;
    chuParameterOptions options;
};

class chuParameterProvider
{
public:
    chuParameterProvider(const String& name, ValueTree source);
    
    virtual ~chuParameterProvider() {}
    virtual void getParamList(std::vector<chuParameter*>& params) = 0;

    String getName();
    ValueTree getData() { return data; }

    PropertyPanel* createPanel();

protected:
    ValueTree data;
};


#endif  // CHUPARAMETER_H_INCLUDED
