/*
  ==============================================================================

    chuLookAndFeel.cpp
    Created: 8 Jan 2016 10:03:38pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuLookAndFeel.h"

chuLookAndFeel::chuLookAndFeel()
{
    setColour(TextButton::ColourIds::textColourOnId, Colours::black);
    setColour(TextButton::ColourIds::textColourOffId, Colours::white);
    setColour(TextButton::ColourIds::buttonColourId, Colours::grey);
    setColour(TextButton::ColourIds::buttonOnColourId, Colours::skyblue);
    
    setColour(PropertyComponent::ColourIds::labelTextColourId, Colours::white);
    setColour(Label::textColourId, Colours::white);
    setColour(Slider::textBoxTextColourId, Colours::white);
    setColour(Slider::ColourIds::thumbColourId, Colours::steelblue);
}

void chuLookAndFeel::drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
                                           bool isMouseOverButton, bool isButtonDown)
{
    Colour baseColour (backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                       .withMultipliedAlpha (button.isEnabled() ? 0.9f : 0.5f));

    if (isButtonDown || isMouseOverButton)
        baseColour = baseColour.contrasting (isButtonDown ? 0.2f : 0.1f);

    const bool flatOnLeft   = button.isConnectedOnLeft();
    const bool flatOnRight  = button.isConnectedOnRight();
    const bool flatOnTop    = button.isConnectedOnTop();
    const bool flatOnBottom = button.isConnectedOnBottom();

    const float width  = button.getWidth() - 1.0f;
    const float height = button.getHeight() - 1.0f;

    if (width > 0 && height > 0)
    {
        const float cornerSize = 4.0f;

        Path outline;
        outline.addRoundedRectangle (0.5f, 0.5f, width, height, cornerSize, cornerSize,
                                     ! (flatOnLeft  || flatOnTop),
                                     ! (flatOnRight || flatOnTop),
                                     ! (flatOnLeft  || flatOnBottom),
                                     ! (flatOnRight || flatOnBottom));

        g.setColour(baseColour);
        g.fillPath(outline);
    }
}

void chuLookAndFeel::drawPropertyPanelSectionHeader (Graphics& g, const String& name,
                                                     bool isOpen, int width, int height)
{
    const float buttonSize = height * 0.75f;
    const float buttonIndent = (height - buttonSize) * 0.5f;

    g.setColour(Colours::darkgrey);
    g.fillRect(0, 0, width, height);
    drawTreeviewPlusMinusBox (g, Rectangle<float> (buttonIndent, buttonIndent, buttonSize, buttonSize), Colours::darkgrey, isOpen, false);

    const int textX = (int) (buttonIndent * 2.0f + buttonSize + 2.0f);

    g.setColour (Colours::white);
    g.setFont (Font (height * 0.7f, Font::bold));
    g.drawText (name, textX, 0, width - textX - 4, height, Justification::centredLeft, true);
}