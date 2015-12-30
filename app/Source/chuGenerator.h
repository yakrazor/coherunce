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

class GeneratorParameterFloat {
public:
    GeneratorParameterFloat(String _name, float _min, float _max, float _defaultValue);
    String name;
    float minValue;
    float maxValue;
    float defaultValue;
    float value;
};

class chuGenerator {
public:
    chuGenerator(String generatorName) : name(generatorName) { init(); };
    virtual ~chuGenerator() {}

    String getName() const { return name; }
    bool isActive() const { return active; }
    void setActive(bool b) { active = b; }

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

class chuGenTenPoints : public chuGenerator {
public:
    chuGenTenPoints() : chuGenerator("TenPoints") {}
    virtual std::vector<PatternItem> getPatterns() override;
};

class chuGenSpirograph : public chuGenerator {
public:
    chuGenSpirograph() : chuGenerator("Spirograph") {}
    virtual std::vector<PatternItem> getPatterns() override;
};


#endif  // CHUGENERATOR_H_INCLUDED
