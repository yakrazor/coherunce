/*
  ==============================================================================

    chuGenerator.h
    Created: 30 Dec 2015 1:32:56pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUGENERATOR_H_INCLUDED
#define CHUGENERATOR_H_INCLUDED

#include <vector>
#include "../JuceLibraryCode/JuceHeader.h"
#include "PatternItem.h"

class GeneratorParameterFloat : public OSCReceiver::ListenerWithOSCAddress<OSCReceiver::RealtimeCallback> {
public:
    GeneratorParameterFloat(String _name, float _min, float _max, float _defaultValue, bool _userVisible = true);
    virtual void oscMessageReceived(const OSCMessage &message) override;

    String name;
    float minValue;
    float maxValue;
    float defaultValue;
    float value;
    bool userVisible;
};

class chuGenerator {
public:
    chuGenerator(String generatorName);
    virtual ~chuGenerator() {}

    String getName() const { return name; }
    bool isActive() const { return active; }
    void setActive(bool b) { active = b; }

    void setOSCAddress(const String& addr);

    virtual void init() {};
    virtual std::vector<PatternItem> getPatterns() = 0;
    virtual void getParams(std::vector<GeneratorParameterFloat*>& params) {};

private:
    String name;
    bool active;
};

class chuGenPolygonPinwheel : public chuGenerator {
public:
    chuGenPolygonPinwheel();
    virtual std::vector<PatternItem> getPatterns() override;
    virtual void getParams(std::vector<GeneratorParameterFloat*>& params) override;
    ScopedPointer<GeneratorParameterFloat> sides;
    ScopedPointer<GeneratorParameterFloat> radius;
    ScopedPointer<GeneratorParameterFloat> copies;
};

class chuGenFivePoints : public chuGenerator {
public:
    chuGenFivePoints();
    virtual std::vector<PatternItem> getPatterns() override;
    virtual void getParams(std::vector<GeneratorParameterFloat*>& params) override;

    static constexpr float leapXMin = -300.0;
    static constexpr float leapXMax = 300.0;
    static constexpr float leapYMin = 60.0;
    static constexpr float leapYMax = 360.0;

    ScopedPointer<GeneratorParameterFloat> sides;
    ScopedPointer<GeneratorParameterFloat> radius;

    ScopedPointer<GeneratorParameterFloat> red;
    ScopedPointer<GeneratorParameterFloat> green;
    ScopedPointer<GeneratorParameterFloat> blue;


    ScopedPointer<GeneratorParameterFloat> pt1x;
    ScopedPointer<GeneratorParameterFloat> pt1y;
    ScopedPointer<GeneratorParameterFloat> pt1on;
    ScopedPointer<GeneratorParameterFloat> pt2x;
    ScopedPointer<GeneratorParameterFloat> pt2y;
    ScopedPointer<GeneratorParameterFloat> pt2on;
    ScopedPointer<GeneratorParameterFloat> pt3x;
    ScopedPointer<GeneratorParameterFloat> pt3y;
    ScopedPointer<GeneratorParameterFloat> pt3on;
    ScopedPointer<GeneratorParameterFloat> pt4x;
    ScopedPointer<GeneratorParameterFloat> pt4y;
    ScopedPointer<GeneratorParameterFloat> pt4on;
    ScopedPointer<GeneratorParameterFloat> pt5x;
    ScopedPointer<GeneratorParameterFloat> pt5y;
    ScopedPointer<GeneratorParameterFloat> pt5on;
};

class chuGenSpirograph : public chuGenerator {
public:
    chuGenSpirograph() : chuGenerator("Spirograph") {}
    virtual std::vector<PatternItem> getPatterns() override;
};


#endif  // CHUGENERATOR_H_INCLUDED
