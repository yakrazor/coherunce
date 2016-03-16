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
        setMethod("setColor", setColor);
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
                else if (args.arguments[0] == "barClock")
                {
                    result = thisObject->generator->localBarClock;
                }
            }
        }
        return result;
    }

    static var addPoint(const var::NativeFunctionArgs& args)
    {
        if (args.numArguments == 2 &&
            (args.arguments[0].isDouble() || args.arguments[0].isInt() || args.arguments[0].isInt64()) &&
            (args.arguments[1].isDouble() || args.arguments[1].isInt() || args.arguments[1].isInt64()))
        {
            float x = static_cast<float>(args.arguments[0]);
            float y = static_cast<float>(args.arguments[1]);
            if (!std::isfinite(x) || !std::isfinite(y))
            {
                return var::undefined();
            }
            
            if (InteropObject* thisObject = dynamic_cast<InteropObject*> (args.thisObject.getObject()))
            {
                
                thisObject->generator->patternBuffer.back().polyline.addPoint(
                    Vector2f(x, y),
                    thisObject->generator->currentColour
                );
            }
        }
        return var::undefined();
    }

    static var setColor(const var::NativeFunctionArgs& args)
    {
        if (args.numArguments == 3)
        {
            if (InteropObject* thisObject = dynamic_cast<InteropObject*> (args.thisObject.getObject()))
            {
                thisObject->generator->currentColour =
                    Colour::fromRGB((int)args.arguments[0], (int)args.arguments[1], (int)args.arguments[2]);
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
    addParameter(a = new chuParameterFloat("a", 0.0, 1.0, 0.5));
    addParameter(b = new chuParameterFloat("b", 0.0, 1.0, 0.5));
    addParameter(c = new chuParameterFloat("c", 0.0, 1.0, 0.5));
    addParameter(d = new chuParameterFloat("d", 0.0, 1.0, 0.5));

    addParameter(code = new chuParameterString("Code",
                                  "var a = g.getParameter('a');\n" \
                                  "var b = g.getParameter('b');\n" \
                                  "var d = g.getParameter('c');\n" \
                                  "var c = g.getParameter('d');\n" \
                                  "var clk = 1.0 - g.getParameter('barClock');\n\n" \
                                  "// add points with g.addPoint(x, y)\n" \
                                  "// change color with g.setColor(r, g, b) [0-255]\n"
                                  ));

    engine.maximumExecutionTime = RelativeTime::seconds(5);
    engine.registerNativeObject("g", new InteropObject(this));

    currentColour = Colours::red;
}

std::vector<PatternItem> chuGenJavascript::getPatterns(float barClock)
{
    patternBuffer.clear();
    PatternItem item;
    item.type = Polyline;
    patternBuffer.push_back(item);
    localBarClock = barClock;
    
    engine.execute(code->getValue());

    return patternBuffer;
}
