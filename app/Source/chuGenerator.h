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
#include "chuParameter.h"


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
    virtual void getParamList(std::vector<chuParameter*>& params) {};

private:
    String name;
    bool active;
};

class chuGenPolygonPinwheel : public chuGenerator {
public:
    chuGenPolygonPinwheel();
    virtual std::vector<PatternItem> getPatterns() override;
    virtual void getParamList(std::vector<chuParameter*>& params) override;
    ScopedPointer<chuParameterFloat> sides;
    ScopedPointer<chuParameterFloat> radius;
    ScopedPointer<chuParameterFloat> copies;
    ScopedPointer<chuParameterColor> color;
};

class chuGenFivePoints : public chuGenerator {
public:
    chuGenFivePoints();
    virtual std::vector<PatternItem> getPatterns() override;
    virtual void getParamList(std::vector<chuParameter*>& params) override;

    static constexpr float leapXMin = -300.0;
    static constexpr float leapXMax = 300.0;
    static constexpr float leapYMin = 60.0;
    static constexpr float leapYMax = 360.0;

    ScopedPointer<chuParameterFloat> sides;
    ScopedPointer<chuParameterFloat> radius;
    ScopedPointer<chuParameterColor> color;

    ScopedPointer<chuParameterFloat> pt1x;
    ScopedPointer<chuParameterFloat> pt1y;
    ScopedPointer<chuParameterFloat> pt1on;
    ScopedPointer<chuParameterFloat> pt2x;
    ScopedPointer<chuParameterFloat> pt2y;
    ScopedPointer<chuParameterFloat> pt2on;
    ScopedPointer<chuParameterFloat> pt3x;
    ScopedPointer<chuParameterFloat> pt3y;
    ScopedPointer<chuParameterFloat> pt3on;
    ScopedPointer<chuParameterFloat> pt4x;
    ScopedPointer<chuParameterFloat> pt4y;
    ScopedPointer<chuParameterFloat> pt4on;
    ScopedPointer<chuParameterFloat> pt5x;
    ScopedPointer<chuParameterFloat> pt5y;
    ScopedPointer<chuParameterFloat> pt5on;
};

class chuGenSpirograph : public chuGenerator {
public:
    chuGenSpirograph() : chuGenerator("Spirograph") {}
    virtual std::vector<PatternItem> getPatterns() override;
};


#endif  // CHUGENERATOR_H_INCLUDED
