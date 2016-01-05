/*
  ==============================================================================

    chuPreferencesPageLaser.cpp
    Created: 25 Dec 2015 7:56:45pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuApplication.h"
#include "chuPreferencesDialog.h"

class chuPreferencePageLaserContent : public Component,
    public ChangeListener,
    private ComboBoxListener,
    private ButtonListener
{
public:
    chuPreferencePageLaserContent()
    {
        updateAllControls();
    }

    ~chuPreferencePageLaserContent()
    {
    }

    void resized() override
    {
        Rectangle<int> r (proportionOfWidth (0.35f), 0, proportionOfWidth (0.6f), 3000);
        int h = 26;
        int space = h / 4;

        r.removeFromTop(space * 2);

        if (outputDeviceDropDown != nullptr)
        {
            auto row = r.removeFromTop(h);
            outputDeviceDropDown->setBounds(row);
            outputDeviceLabel->setBounds(0, outputDeviceDropDown->getBounds().getCentreY() - h / 2, r.getX(), h);
        }

        r.removeFromTop(space * 2);

        if (calibrateButton != nullptr)
        {
            calibrateButton->setBounds(r.removeFromTop(h));
            calibrateButton->changeWidthToFitText();
        }

        r.removeFromTop(space * 2);

        if (testButton != nullptr)
        {
            testButton->setBounds(r.removeFromTop(h));
            testButton->changeWidthToFitText();
        }
    }

    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override
    {
        if (comboBoxThatHasChanged == nullptr)
        {
            return;
        }
        else if (comboBoxThatHasChanged == outputDeviceDropDown)
        {
            if (outputDeviceDropDown->getSelectedId() > 0)
            {
                // TODO: implement me
            }
        }
    }

    void buttonClicked (Button* button) override
    {
        if (button == calibrateButton)
        {
        }
        else if (button == testButton)
        {
        }
    }

    void updateAllControls()
    {
        updateOutputsComboBox();
        updateButtons();
        updatePropertyPanel();
    }

    void changeListenerCallback (ChangeBroadcaster*) override
    {
        updateAllControls();
    }


private:

    ScopedPointer<ComboBox> outputDeviceDropDown;
    ScopedPointer<TextButton> calibrateButton, testButton;
    ScopedPointer<Label> outputDeviceLabel;
    ScopedPointer<PropertyPanel> laserProperties;
    OwnedArray<Component> childControls;

    static String getNoDeviceString()   { return "<< " + TRANS("none") + " >>"; }

    int getLowestY() const
    {
        int y = 0;

        for (int i = getNumChildComponents(); --i >= 0;)
            y = jmax (y, getChildComponent (i)->getBottom());

        return y;
    }

    void updateOutputsComboBox()
    {
        if (outputDeviceDropDown == nullptr)
        {
            outputDeviceDropDown = new ComboBox (String::empty);
            outputDeviceDropDown->addListener (this);
            addAndMakeVisible (outputDeviceDropDown);

            outputDeviceLabel = new Label(String::empty, "Laser device:");
            outputDeviceLabel->setJustificationType(Justification::centredRight);
            outputDeviceLabel->attachToComponent(outputDeviceDropDown, true);
            addAndMakeVisible(outputDeviceLabel);
        }

        outputDeviceDropDown->clear(dontSendNotification);

        std::vector<String> devices = { "Etherdream DAC" };
        
        for (int i = 0; i < devices.size(); ++i)
            outputDeviceDropDown->addItem(devices[i], i + 1);

        outputDeviceDropDown->addItem(getNoDeviceString(), -1);
        outputDeviceDropDown->setSelectedId(-1, dontSendNotification);
    }

    void updateButtons()
    {
        if (calibrateButton == nullptr)
        {
            calibrateButton = new TextButton("Calibrate");
            addAndMakeVisible(calibrateButton);
        }
        if (testButton == nullptr)
        {
            testButton = new TextButton("Show Test Pattern");
            addAndMakeVisible(testButton);
        }
    }

    void updatePropertyPanel()
    {
        if (laserProperties == nullptr)
        {
            laserProperties = getApp()->getLaserOutputThread()->getLaserConfig().createPanel();
            laserProperties->setBounds(12, 130, 430, 200);
            addAndMakeVisible(laserProperties);
        }
    }
};

class chuPreferencesPageLaser : public Component
{
public:
    chuPreferencesPageLaser()
    {
        laserContent = new chuPreferencePageLaserContent();
        addAndMakeVisible(laserContent);

        addAndMakeVisible(diagnosticsBox);
        diagnosticsBox.setMultiLine(true);
        diagnosticsBox.setReturnKeyStartsNewLine(true);
        diagnosticsBox.setReadOnly(true);
        diagnosticsBox.setScrollbarsShown(true);
        diagnosticsBox.setCaretVisible(false);
        diagnosticsBox.setPopupMenuEnabled(true);
        diagnosticsBox.setColour(TextEditor::textColourId, Colours::white);
        diagnosticsBox.setColour(TextEditor::backgroundColourId, Colour (0x32ffffff));
        diagnosticsBox.setColour(TextEditor::outlineColourId, Colour (0x1c000000));
        diagnosticsBox.setColour(TextEditor::shadowColourId, Colour (0x16000000));

        logMessage ("Laser device diagnostics:\n");
        dumpDeviceInfo();
    }

    ~chuPreferencesPageLaser()
    {
        diagnosticsBox.clear();
    }

    void paint (Graphics& g)
    {
        g.fillAll(Colours::skyblue);
    }

    void resized()
    {
        Rectangle<int> r(getLocalBounds().reduced(4));
        laserContent->setBounds(r.removeFromTop(proportionOfHeight(0.65f)));
        diagnosticsBox.setBounds(r);
    }

    void dumpDeviceInfo()
    {
        // TODO: implement me
        logMessage("\nTODO: implement me\n");

        /*
        if (connected)
        {

        }
        else
        {
            logMessage("No laser DACs found");
        }
        */
    }

    void logMessage(const String& m)
    {
        diagnosticsBox.moveCaretToEnd();
        diagnosticsBox.insertTextAtCaret(m + newLine);
    }

private:
    TextEditor diagnosticsBox;
    ScopedPointer<chuPreferencePageLaserContent> laserContent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (chuPreferencesPageLaser)
};

static chuPreferencePageProvider<chuPreferencesPageLaser> page("Laser");
