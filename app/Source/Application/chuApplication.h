/*
  ==============================================================================

    chuApplication.h
    Created: 24 Dec 2015 11:32:55pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "LaserOutputThread.h"
#include "chuMainWindow.h"
#include "chuFrameTimer.h"
#include "chuProject.h"


enum CommandIDs {
    About = 0x2000,
    Preferences,
    Open,
    Save,
    SaveAs,
    HelpContents,
    CloseWindow,
    Rename
};


class chuApplication  : public JUCEApplication
{
public:
    chuApplication() {}

    const String getApplicationName() override       { return CharPointer_UTF8("coher\xc3\xbcnce") ; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    void initialise(const String& commandLine) override;
    void shutdown() override;

    void systemRequestedQuit() override;

    void anotherInstanceStarted(const String& commandLine) override;

    ApplicationCommandManager& getApplicationCommandManager();
    AudioDeviceManager& getSharedAudioDeviceManager();

    void setExternalClockSource(const String& deviceName);

    Component& getSettingsWindow();

    // ApplicationCommandTarget interface
    ApplicationCommandTarget* getNextCommandTarget() override;
    void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) override;
    void getAllCommands(Array<CommandID>& commands) override;
    bool perform(const InvocationInfo& info) override;

    LaserOutputThread* getLaserOutputThread() { return laserThread; }
    chuFrameTimer* getFrameTimer() { return frameTimer; }

    chuProject* getCurrentProject() { return currentProject; }
    
private:
    ScopedPointer<Component> mainWindow;
    ScopedPointer<Component> settingsWindow;
    ScopedPointer<MenuBarModel> mainMenu;
    ScopedPointer<LaserOutputThread> laserThread;
    ScopedPointer<ApplicationCommandManager> applicationCommandManager;
    ScopedPointer<AudioDeviceManager> sharedAudioDeviceManager;
    ScopedPointer<chuFrameTimer> frameTimer;

    ScopedPointer<chuProject> currentProject;

    String externalClockMidiDeviceName;
};

inline chuApplication* getApp()
{
    return static_cast<chuApplication*>(JUCEApplication::getInstance());
}

inline chuMainWindow* getMainWindow()
{
    for (int i = TopLevelWindow::getNumTopLevelWindows(); --i >= 0;)
        if (chuMainWindow* maw = dynamic_cast<chuMainWindow*> (TopLevelWindow::getTopLevelWindow (i)))
            return maw;

    return nullptr;
}

#endif  // MAIN_H_INCLUDED
