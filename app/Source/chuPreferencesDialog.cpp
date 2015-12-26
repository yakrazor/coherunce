/*
  ==============================================================================

    SettingsWindow.cpp
    Created: 24 Dec 2015 10:54:15pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "chuPreferencesDialog.h"
#include "chuPreferencesPageLaser.h"
#include "chuPreferencesPageAudio.h"


class chuPreferencesDialogContent : public Component, public ListBoxModel
{
public:
    chuPreferencesDialogContent() {
        const unsigned int sidebarWidth = 160;
        const unsigned int contentWidth = 400;
        const unsigned int height = 600;

        pageList = new ListBox();
        pageList->setModel(this);
        pageList->setBounds(0, 0, sidebarWidth, height);
        pageList->setRowHeight(35);
        pageList->setColour(ListBox::ColourIds::backgroundColourId, Colours::transparentBlack);
        addAndMakeVisible(pageList);

        audioPage = new chuPreferencesPageAudio();
        audioPage->setBounds(sidebarWidth, 0, contentWidth, height);
        addChildComponent(audioPage);

        laserPage = new chuPreferencesPageLaser();
        laserPage->setBounds(sidebarWidth, 0, contentWidth, height);
        addChildComponent(laserPage);

        setBounds(0, 0, contentWidth + sidebarWidth, height);
        pageList->selectRow(0);
    }

    int getNumRows() override {
        return 2;
    }

    void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override
    {
        if (rowIsSelected)
        {
            g.fillAll(Colours::skyblue);
        } else {
            g.fillAll(Colours::black);
        }

        AttributedString a;
        a.setJustification (Justification::centredLeft);
        Font font;
        font.setBold(true);

        if (rowNumber == 0) {
            a.append("L", font, Colours::red);
            a.append("a", font, Colours::orange);
            a.append("s", font, Colours::forestgreen);
            a.append("e", font, Colours::blueviolet);
            a.append("r", font, Colours::purple);
        } else if (rowNumber == 1) {
            a.append("Audio/MIDI", font, Colours::white);

        }

        a.draw(g, Rectangle<int> (width + 10, height).reduced (6, 0).toFloat());
        
    }

    void paint(Graphics& g) override
    {
        g.fillAll(Colours::black);

    }

    void selectedRowsChanged(int lastRowSelected) override
    {
        if (lastRowSelected == 0) {
            laserPage->setVisible(true);
            audioPage->setVisible(false);
        } else {
            laserPage->setVisible(false);
            audioPage->setVisible(true);
        }
    }

private:
    ScopedPointer<ListBox> pageList;
    ScopedPointer<Component> audioPage;
    ScopedPointer<Component> laserPage;
};

//==============================================================================
chuPreferencesDialog::chuPreferencesDialog()
: DocumentWindow("Preferences", Colours::lightgrey, DocumentWindow::closeButton)
{
    setUsingNativeTitleBar(true);
    setContentOwned(new chuPreferencesDialogContent(), true);
    setResizable(false, false);

    addKeyListener(getApp()->getApplicationCommandManager().getKeyMappings());

    centreWithSize(getWidth(), getHeight());
}

chuPreferencesDialog::~chuPreferencesDialog()
{
    deleteAllChildren();
}

void chuPreferencesDialog::paint(Graphics& g)
{
     g.fillAll(Colours::silver);
}


void chuPreferencesDialog::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}

void chuPreferencesDialog::closeButtonPressed()
{
    setVisible(false);
}
