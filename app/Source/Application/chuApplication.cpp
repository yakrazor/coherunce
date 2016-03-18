/*
 ==============================================================================

 chuApplication.cpp
 Created: 24 Dec 2015 11:32:55pm
 Author:  Michael Dewberry

 ==============================================================================
 */

#include "chuApplication.h"
#include "chuPreferencesDialog.h"
#include "chuMainWindow.h"
#include "chuMenuBar.h"
#include "chuOSCManager.h"
#include "chuGeneratorManager.h"


#define FRAME_RATE 30




void chuApplication::initialise(const String& commandLine)
{
    chuOSCManager::initialize(7900);

    laserThread = new LaserOutputThread();
    laserThread->startThread();

    frameTimer = new chuFrameTimer(laserThread);
    frameTimer->startTimerHz(FRAME_RATE);

    externalClockMidiDeviceName = "";
    
    int index = MidiInput::getDefaultDeviceIndex();
    if (index >= 0)
    {
        setExternalClockSource(MidiInput::getDevices()[index]);
    }

    auto menu = new chuMenuBar();
    getApplicationCommandManager().registerAllCommandsForTarget(this);
    menu->initialize();
    mainMenu = menu;

    currentProject = new chuProject();
    currentProject->loadFromFile("../../../../../files/default.chu");

    mainWindow = new chuMainWindow(getApplicationName());
    settingsWindow = new chuPreferencesDialog();

}

void chuApplication::shutdown()
{
    chuOSCManager::deinitialize();

    mainMenu = nullptr;
    mainWindow = nullptr;
    settingsWindow = nullptr;

    laserThread->getOutputBuffer().getPatternQueue().finish_frame();
    laserThread->disableOutput();
    laserThread->stopThread(200);
    laserThread = nullptr;

    applicationCommandManager = nullptr;
    sharedAudioDeviceManager = nullptr;
    clearGeneratorManager();

    while (auto window = TopLevelWindow::getActiveTopLevelWindow())
    {
        delete window;
    }
}

void chuApplication::systemRequestedQuit()
{
    quit();
}

void chuApplication::anotherInstanceStarted (const String& commandLine)
{
}

ApplicationCommandManager& chuApplication::getApplicationCommandManager()
{
    if (applicationCommandManager == nullptr)
        applicationCommandManager = new ApplicationCommandManager();

    return *applicationCommandManager;
}

AudioDeviceManager& chuApplication::getSharedAudioDeviceManager()
{
    if (sharedAudioDeviceManager == nullptr)
    {
        sharedAudioDeviceManager = new AudioDeviceManager();
        sharedAudioDeviceManager->initialise (2, 2, 0, true, String(), 0);
    }

    return *sharedAudioDeviceManager;
}

void chuApplication::setExternalClockSource(const String& deviceName)
{
    if (frameTimer)
    {
        if (externalClockMidiDeviceName != "")
        {
            getSharedAudioDeviceManager().removeMidiInputCallback(externalClockMidiDeviceName, frameTimer);
        }
        externalClockMidiDeviceName = deviceName;
        
        getSharedAudioDeviceManager().setMidiInputEnabled(deviceName, true);
        getSharedAudioDeviceManager().addMidiInputCallback(deviceName, frameTimer);
    }
}

Component& chuApplication::getSettingsWindow()
{
    return *settingsWindow;
}

ApplicationCommandTarget* chuApplication::getNextCommandTarget()
{
    return nullptr;
}

void chuApplication::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
    switch (commandID)
    {
        case CommandIDs::About:
            result.setInfo(CharPointer_UTF8("About coher\xc3\xbcnce"), "Version and credits", "General", 0);
            return;
        case CommandIDs::Preferences:
            result.setInfo("Preferences...", "Application and device preferences", "General", 0);
            result.addDefaultKeypress(',', ModifierKeys::commandModifier);
            return;
        case CommandIDs::Open:
            result.setInfo("Open...", "Open an existing project", "General", 0);
            result.addDefaultKeypress('O', ModifierKeys::commandModifier);
            return;
        case CommandIDs::Save:
            result.setInfo("Save", "Save the current project", "General", 0);
            result.addDefaultKeypress('S', ModifierKeys::commandModifier);
            return;
        case CommandIDs::SaveAs:
            result.setInfo("Save As...", "Save the current project under a different filename", "General", 0);
            result.addDefaultKeypress('S', ModifierKeys::commandModifier|ModifierKeys::shiftModifier);
            return;
        case CommandIDs::HelpContents:
            result.setInfo(CharPointer_UTF8("coher\xc3\xbcnce Manual"), "Open the user manual", "Help", 0);
            return;
        case CommandIDs::CloseWindow:
            result.setInfo("Close Window", "Close the active window", "General", 0);
            result.addDefaultKeypress('W', ModifierKeys::commandModifier);
            return;
        case CommandIDs::Rename:
            result.setInfo("Rename", "Renames the selected item", "General", 0);
            result.addDefaultKeypress('R', ModifierKeys::commandModifier);
            return;
        case StandardApplicationCommandIDs::undo:
            result.setInfo("Undo", "Undoes the last action", "General", 0);
            result.addDefaultKeypress('Z', ModifierKeys::commandModifier);
            return;
        case StandardApplicationCommandIDs::redo:
            result.setInfo("Redo", "Redoes the last undone action", "General", 0);
            result.addDefaultKeypress('Z', ModifierKeys::commandModifier|ModifierKeys::shiftModifier);
            return;
        case StandardApplicationCommandIDs::cut:
            result.setInfo("Cut", "Removes the selection and places it on the clipboard", "General", 0);
            result.addDefaultKeypress('X', ModifierKeys::commandModifier);
            result.setActive(false);
            return;
        case StandardApplicationCommandIDs::copy:
            result.setInfo("Copy", "Copies the selection to the clipboard", "General", 0);
            result.addDefaultKeypress('C', ModifierKeys::commandModifier);
            result.setActive(false);
            return;
        case StandardApplicationCommandIDs::paste:
            result.setInfo("Paste", "Inserts the contents of the clipboard", "General", 0);
            result.addDefaultKeypress('V', ModifierKeys::commandModifier);
            result.setActive(false);
            return;
        case StandardApplicationCommandIDs::del:
            result.setInfo("Delete", "Deletes the selection", "General", 0);
            result.addDefaultKeypress(KeyPress::backspaceKey, 0);
            result.setActive(true);
            return;
    }
    JUCEApplication::getCommandInfo(commandID, result);
}

void chuApplication::getAllCommands(Array<CommandID>& commands)
{
    commands.add(CommandIDs::About);
    commands.add(CommandIDs::Preferences);
    commands.add(CommandIDs::Open);
    commands.add(CommandIDs::Save);
    commands.add(CommandIDs::SaveAs);
    commands.add(CommandIDs::HelpContents);
    commands.add(CommandIDs::CloseWindow);
    commands.add(CommandIDs::Rename);
    commands.add(StandardApplicationCommandIDs::undo);
    commands.add(StandardApplicationCommandIDs::redo);
    commands.add(StandardApplicationCommandIDs::cut);
    commands.add(StandardApplicationCommandIDs::copy);
    commands.add(StandardApplicationCommandIDs::paste);
    commands.add(StandardApplicationCommandIDs::del);

    JUCEApplication::getAllCommands(commands);
}

bool chuApplication::perform(const InvocationInfo& info)
{
    switch (info.commandID)
    {
        case CommandIDs::About:
            // TODO: implement me
            return true;
        case CommandIDs::Preferences:
            getApp()->getSettingsWindow().setVisible(true);
            return true;
        case CommandIDs::Open:
            {
                FileChooser fc ("Open Project...",
                                File::getCurrentWorkingDirectory(),
                                "*.chu",
                                true);
                fc.browseForFileToOpen();

                if (currentProject) {
                    // todo: warn about unsaved changes
                } else {
                    currentProject = new chuProject();
                }
                mainWindow = nullptr;
                getGeneratorManager()->getAllGenerators().clear();
                currentProject->loadFromFile(fc.getResult());
                mainWindow = new chuMainWindow(getApplicationName());
            }
            return true;
        case CommandIDs::Save:
            if (currentProject) {
                currentProject->saveToFile();
            }
            return true;
        case CommandIDs::SaveAs:
            if (currentProject) {
                FileChooser fc ("Save As...",
                                File::getCurrentWorkingDirectory(),
                                "*.chu",
                                true);
                fc.browseForFileToSave(true);

                currentProject->saveToFile(fc.getResult());
            }
            return true;
        case CommandIDs::HelpContents:
            // TODO: implement me
            return true;
        case CommandIDs::CloseWindow:
            {
                auto window = TopLevelWindow::getActiveTopLevelWindow();
                if (window == &getSettingsWindow())
                {
                    window->setVisible(false);
                }
                else if (window != getMainWindow())
                {
                    delete window;
                }
                return true;
            }
        case CommandIDs::Rename:
            if (getGeneratorManager()->getCurrentGenerator())
            {
                String name = getGeneratorManager()->getCurrentGenerator()->getName();

                AlertWindow window("Rename", "", AlertWindow::NoIcon, nullptr);
                window.addTextEditor("name", name);
                window.addButton("OK", 1, KeyPress(KeyPress::returnKey));
                window.addButton("Cancel", 0, KeyPress(KeyPress::escapeKey));
                if (window.runModalLoop())
                {
                    name = window.getTextEditorContents("name");
                    getGeneratorManager()->renameGenerator(getGeneratorManager()->getCurrentGenerator(), name);
                }
            }
            return true;

        case StandardApplicationCommandIDs::undo:
            // TODO: implement me
            return true;
        case StandardApplicationCommandIDs::redo:
            // TODO: implement me
            return true;
            
        // should be handled by components
        case StandardApplicationCommandIDs::cut:
            return false;
        case StandardApplicationCommandIDs::copy:
            return false;
        case StandardApplicationCommandIDs::paste:
            return false;

        case StandardApplicationCommandIDs::del:
            getMainWindow()->getClipGrid()->deleteGenerator(getGeneratorManager()->getCurrentGenerator());
            return true;

    }

    return JUCEApplication::perform(info);
}


START_JUCE_APPLICATION(chuApplication)

