/*
  ==============================================================================

    SettingsWindow.cpp
    Created: 24 Dec 2015 10:54:15pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "chuPreferencesDialog.h"
#include "chuApplication.h"

chuPreferencePageProviderBase::chuPreferencePageProviderBase(const String& pageName)
: name(pageName)
{
    getPageTypeList().add(this);
}

chuPreferencePageProviderBase::~chuPreferencePageProviderBase()
{
    getPageTypeList().removeFirstMatchingValue(this);
}

Array<chuPreferencePageProviderBase*>& chuPreferencePageProviderBase::getPageTypeList()
{
    static Array<chuPreferencePageProviderBase*> list;
    return list;
}

class chuPreferencesDialogContent : public Component, public ListBoxModel
{
public:

    const unsigned int sidebarWidth = 90;
    const unsigned int contentWidth = 450;
    const unsigned int height = 600;
    const unsigned int margin = 4;

    chuPreferencesDialogContent() {
        pageList = new ListBox();
        pageList->setModel(this);
        pageList->setBounds(0, margin, sidebarWidth, height);
        pageList->setRowHeight(35);
        pageList->setColour(ListBox::ColourIds::backgroundColourId, Colours::transparentBlack);
        addAndMakeVisible(pageList);

        for (auto& pageProvider : chuPreferencePageProviderBase::getPageTypeList()) {
            Component* page = pageProvider->createComponent();
            page->setBounds(sidebarWidth, margin, contentWidth, height);
            addChildComponent(page);
            pages.add(page);
        }

        setBounds(0, 0, contentWidth + sidebarWidth + margin * 2, height + margin * 3);
        pageList->selectRow(0);
    }

    int getNumRows() override {
        return chuPreferencePageProviderBase::getPageTypeList().size();
    }

    void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override
    {
        if (rowIsSelected)
        {
            g.fillAll(Colours::skyblue);
            g.setColour(Colours::black);
            g.fillRect(0, height - margin, margin, margin);
            g.setColour(Colours::grey);
            g.fillRect((int)margin, height - margin, width - margin, margin);
        } else {
            g.fillAll(Colours::black);
        }

        AttributedString a;
        a.setJustification (Justification::centredLeft);
        Font font;
        font.setBold(true);

        String pageName = chuPreferencePageProviderBase::getPageTypeList()[rowNumber]->name;

        if (pageName == "Laser") {
            a.append("L", font, Colours::red);
            a.append("a", font, Colours::orange);
            a.append("s", font, Colours::forestgreen);
            a.append("e", font, Colours::blueviolet);
            a.append("r", font, Colours::purple);
        } else {
            a.append(pageName, font, Colours::white);
        }

        a.draw(g, Rectangle<int>(width + 10, height - 2).reduced(6, 0).toFloat());
    }

    void paint(Graphics& g) override
    {
        g.fillAll(Colours::black);
        g.setColour(Colours::grey);
        g.fillRect((int)(sidebarWidth + contentWidth), 2 * margin, margin, height - margin);
        g.fillRect((int)(sidebarWidth + margin), height + margin, contentWidth, margin);
    }

    void selectedRowsChanged(int lastRowSelected) override
    {
        for (auto& page : pages) {
            page->setVisible(false);
        }

        pages[lastRowSelected]->setVisible(true);
    }

private:
    ScopedPointer<ListBox> pageList;
    OwnedArray<Component> pages;
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
     g.fillAll(Colours::black);
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
