/*
  ==============================================================================

    Main.h
    Created: 24 Dec 2015 11:32:55pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "LaserOutputThread.h"
#include "SettingsWindow.h"



Component* createMainContentComponent();


enum CommandIDs {
    About = 0x2000,
    Preferences
};

class MainWindow : public DocumentWindow
{
public:
    MainWindow(String name);
    ~MainWindow();

    void closeButtonPressed() override;

    static MainWindow* getMainWindow();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};


class coherunceApplication  : public JUCEApplication
{
public:
    coherunceApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    void initialise(const String& commandLine) override;
    void shutdown() override;

    void systemRequestedQuit() override;

    void anotherInstanceStarted(const String& commandLine) override;

    ApplicationCommandManager& getApplicationCommandManager();
    AudioDeviceManager& getSharedAudioDeviceManager();
    SettingsWindow& getSettingsWindow();

private:
    ScopedPointer<MainWindow> mainWindow;
    ScopedPointer<SettingsWindow> settingsWindow;
    ScopedPointer<MenuBarModel> mainMenu;
    ScopedPointer<LaserOutputThread> laserThread;
    ScopedPointer<ApplicationCommandManager> applicationCommandManager;
    ScopedPointer<AudioDeviceManager> sharedAudioDeviceManager;

};

inline coherunceApplication* getApp()
{
    return static_cast<coherunceApplication*>(JUCEApplication::getInstance());
}

inline MainWindow* getMainWindow()
{
    for (int i = TopLevelWindow::getNumTopLevelWindows(); --i >= 0;)
        if (MainWindow* maw = dynamic_cast<MainWindow*> (TopLevelWindow::getTopLevelWindow (i)))
            return maw;

    return nullptr;
}

#endif  // MAIN_H_INCLUDED
