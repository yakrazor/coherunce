/*
  ==============================================================================

    chuPreferencesDialog.h
    Created: 24 Dec 2015 10:54:15pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef SETTINGSWINDOW_H_INCLUDED
#define SETTINGSWINDOW_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class chuPreferencesDialog : public DocumentWindow
{
public:
    chuPreferencesDialog();
    ~chuPreferencesDialog();

    void paint(Graphics&);
    void resized();

    void closeButtonPressed() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(chuPreferencesDialog)
};

class chuPreferencePageProviderBase
{
public:
    chuPreferencePageProviderBase(const String& pageName);
    virtual ~chuPreferencePageProviderBase();

    virtual Component* createComponent() = 0;

    const String name;
    static Array<chuPreferencePageProviderBase*>& getPageTypeList();

private:
    JUCE_DECLARE_NON_COPYABLE(chuPreferencePageProviderBase)
};

template <class PageType>
class chuPreferencePageProvider : public chuPreferencePageProviderBase
{
public:
    chuPreferencePageProvider(const String& pageName) : chuPreferencePageProviderBase(pageName)
    {
        int i = 0;
        i++;
    }

    Component* createComponent() { return new PageType(); }

private:
    JUCE_DECLARE_NON_COPYABLE(chuPreferencePageProvider)
};


#endif  // SETTINGSWINDOW_H_INCLUDED
