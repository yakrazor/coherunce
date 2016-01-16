/*
  ==============================================================================

    chuGenJavascript.cpp
    Created: 16 Jan 2016 2:00:43am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuGenJavascript.h"


struct InteropObject : public DynamicObject
{
    InteropObject(chuGenJavascript* jsGen)
    : generator(jsGen)
    {
        setMethod("getParameter", getParameter);
        setMethod("addPoint", addPoint);
    }

    static Identifier getClassName() { return "Graphics"; }

    static var getParameter(const var::NativeFunctionArgs& args)
    {
        var result = var::undefined();
        if (args.numArguments == 1)
        {
            if (InteropObject* thisObject = dynamic_cast<InteropObject*> (args.thisObject.getObject()))
            {
                if (args.arguments[0] == "a")
                {
                    result = thisObject->generator->a->getValue();
                }
                else if (args.arguments[0] == "b")
                {
                    result = thisObject->generator->b->getValue();
                }
                else if (args.arguments[0] == "c")
                {
                    result = thisObject->generator->c->getValue();
                }
                else if (args.arguments[0] == "d")
                {
                    result = thisObject->generator->d->getValue();
                }
            }
        }
        return result;
    }

    static var addPoint(const var::NativeFunctionArgs& args)
    {
        if (args.numArguments == 2)
        {
            if (InteropObject* thisObject = dynamic_cast<InteropObject*> (args.thisObject.getObject()))
            {
                thisObject->generator->patternBuffer.back().points.push_back(
                    Vector2f((float)args.arguments[0], (float)args.arguments[1])
                );
            }
        }
        return var::undefined();
    }

    chuGenJavascript* generator;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InteropObject)
};


chuGenJavascript::chuGenJavascript()
: chuGenerator("CustomJavascript")
{
    a = new chuParameterFloat("a", 0.0, 1.0, 0.5);
    b = new chuParameterFloat("b", 0.0, 1.0, 0.5);
    c = new chuParameterFloat("c", 0.0, 1.0, 0.5);
    d = new chuParameterFloat("d", 0.0, 1.0, 0.5);
    code = new chuParameterString("Code",
                                  "var a = g.getParameter('a');\n" \
                                  "g.addPoint(0,0);\n" \
                                  "g.addPoint(-a, a);\n" \
                                  "g.addPoint(-a, -a);\n" \
                                  "g.addPoint(a, a);\n" \
                                  "g.addPoint(a, -a);\n" \
                                  "g.addPoint(0, 0);\n"
                                  );

    engine.maximumExecutionTime = RelativeTime::seconds(5);
    engine.registerNativeObject("g", new InteropObject(this));
}

void chuGenJavascript::getParamList(std::vector<chuParameter*>& params)
{
    chuGenerator::getParamList(params); // call superclass

    params.push_back(a);
    params.push_back(b);
    params.push_back(c);
    params.push_back(d);
    params.push_back(code);
}

std::vector<PatternItem> chuGenJavascript::getPatterns(float barClock)
{
    patternBuffer.clear();
    PatternItem item;
    item.type = Polyline;
    patternBuffer.push_back(item);
    
    engine.execute(code->getValue());

    return patternBuffer;
}