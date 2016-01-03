/*
  ==============================================================================

    chuParameter.h
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

    // Parameter subclasses must override these two methods:
    virtual Component* createComponent() = 0;
    virtual void oscMessageReceived(const OSCMessage &message) = 0;

    String name;
    chuParameterOptions options;
};

class chuParameterFloat : public chuParameter {
public:
    chuParameterFloat(const String& _name, float _min, float _max, float _defaultValue, const chuParameterOptions& _options = chuParameterOptions::Default);

    virtual Component* createComponent() override;
    virtual void oscMessageReceived(const OSCMessage &message) override;

    float minValue;
    float maxValue;
    float value;
};

class chuParameterInt : public chuParameter {
public:
    chuParameterInt(const String& _name, int _min, int _max, int _defaultValue, const chuParameterOptions& _options = chuParameterOptions::Default);

    virtual Component* createComponent() override;
    virtual void oscMessageReceived(const OSCMessage &message) override;

    int minValue;
    int maxValue;
    int value;
};

typedef Colour Color;
typedef Colours Colors;

class chuParameterColor : public chuParameter {
public:
    chuParameterColor(const String& _name, const Color& _color, const chuParameterOptions& _options = chuParameterOptions::Default);

    virtual Component* createComponent() override;
    virtual void oscMessageReceived(const OSCMessage &message) override;

    Color value;
};



#endif  // CHUPARAMETER_H_INCLUDED
