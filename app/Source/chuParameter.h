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
    virtual ~chuParameterProvider() {}
    virtual void getParamList(std::vector<chuParameter*>& params) = 0;
    virtual String getName() const = 0;

    PropertyPanel* createPanel();
};

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

typedef Colour Color;
typedef Colours Colors;

class chuParameterColor : public chuParameter {
public:
    chuParameterColor(const String& _name, const Color& _color, const chuParameterOptions& _options = chuParameterOptions::Default);
    virtual ~chuParameterColor() {}

    virtual PropertyComponent* createComponent() override;
    virtual void oscMessageReceived(const OSCMessage &message) override;

    Color getValue() const { return Color(value.load()); }
    void setValue(const Color& c) { value.store(c.getARGB()); }

private:
    std::atomic<uint32> value;
};



#endif  // CHUPARAMETER_H_INCLUDED
