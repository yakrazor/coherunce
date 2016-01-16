/*
  ==============================================================================

    chuMultiSplitPane.h
    Created: 11 Jan 2016 4:24:38am
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUMULTISPLITPANE_H_INCLUDED
#define CHUMULTISPLITPANE_H_INCLUDED

#include "../../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
 
 assumptions: 
 - only one child pane is "expandable", all have a fixed width set by dragging a splitter
 - min/max/start width on expandable pane will be ignored
 - parent window must have a minimum resizable width that is greater than the maximum widths of all nonexpandable panes

*/

class chuMultiSplitPane : public Component
{
public:
    chuMultiSplitPane();
    ~chuMultiSplitPane();

    void paint(Graphics&);
    void resized();

    void addPane(Component* pane, int minWidth, int maxWidth, int startWidth, bool expandable = false);

    void setSplitterWidth(int width) { splitterWidth = width; }

private:

    class SplitterBar : public Component
    {
    public:
        SplitterBar(int minWidth, int maxWidth, int startWidth);
        ~SplitterBar();

        void paint(Graphics&);
        void resized();
        void mouseDown(const MouseEvent& e) override;
        void mouseDrag(const MouseEvent& e) override;

        int getWidth() const { return width; }
        int getDirection() const { return direction; }
        void setDirection(int d) { direction = d; }

    private:
        int minWidth;
        int maxWidth;
        int width;
        int direction;

        int startMouseDragOffset;
    };
    
    OwnedArray<SplitterBar> splitters;
    OwnedArray<Component> children;

    int flexComponentIndex;
    int splitterWidth;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(chuMultiSplitPane)
};


#endif  // CHUMULTISPLITPANE_H_INCLUDED
