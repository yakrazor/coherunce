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
    chuParameter(const String& name, const chuParameterOptions& paramOptions = chuParameterOptions::Default);
    virtual ~chuParameter() {}

    // Parameter subclasses must override these three methods:
    virtual void deserialize(ValueTree saved) = 0;
    virtual void oscMessageReceived(const OSCMessage &message) = 0;
    virtual PropertyComponent* createComponent() = 0;

    const String getName() { return data.getProperty("name"); }
    const chuParameterOptions& getOptions() { return options; }

    void listenAtOSCAddress(const String& prefix);

protected:
    friend class chuParameterProvider;
    ValueTree data;
    chuParameterOptions options;
};

class chuParameterProvider
{
public:
    chuParameterProvider(const String& typeName, ValueTree source);
    virtual ~chuParameterProvider();
    
    void getParamList(std::vector<chuParameter*>& params) const;
    virtual const String getOSCRoot() const { return String::empty; }

    const String getType() const;
    const String getName() const;
    virtual void setName(String name);
    ValueTree getData() { return data; }

    void addParameter(chuParameter* newParameter);

    void createPanel(PropertyPanel* panel) const;

protected:
    void remapOSCAddresses();
    void deregisterOSCAddresses();

    OwnedArray<chuParameter> parameters;
    ValueTree data;
};


#endif  // CHUPARAMETER_H_INCLUDED
