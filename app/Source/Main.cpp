

#include "Main.h"



class coherunceMenuBar : public MenuBarModel
{
public:
    coherunceMenuBar()
    {
        setApplicationCommandManagerToWatch(&getApp()->getApplicationCommandManager());
    }

    void initialize()
    {
#if JUCE_MAC
        appleItems = new PopupMenu();
        ApplicationCommandManager* commandManager = &getApp()->getApplicationCommandManager();
        appleItems->addCommandItem(commandManager, CommandIDs::About);
        appleItems->addSeparator();
        appleItems->addCommandItem(commandManager, CommandIDs::Preferences);

        MenuBarModel::setMacMainMenu(this, appleItems, "Open Recent");
#endif
    }

    virtual StringArray getMenuBarNames() override
    {
        const char* const names[] = { "File", "Edit", "Help", nullptr };
        return StringArray (names);
    }

    virtual PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName)
    {
        PopupMenu menu;
        ApplicationCommandManager* commandManager = &getApp()->getApplicationCommandManager();
        if (menuName == "File") {
            menu.addCommandItem(commandManager, CommandIDs::Open);
            PopupMenu recentFiles;
            // TODO: implement for Windows (OSX will populate automatically)
            //settings->recentFiles.createPopupMenuItems (recentFiles, recentProjectsBaseID, true, true);
            menu.addSubMenu("Open Recent", recentFiles);
            menu.addSeparator();
            menu.addCommandItem(commandManager, CommandIDs::Save);
            menu.addSeparator();
#if !JUCE_MAC
            menu.addSeparator();
            menu.addCommandItem(commandManager, StandardApplicationCommandIDs::quit);
#endif
        } else if (menuName == "Edit") {
            menu.addCommandItem(commandManager, StandardApplicationCommandIDs::undo);
            menu.addCommandItem(commandManager, StandardApplicationCommandIDs::redo);
            menu.addSeparator();
            menu.addCommandItem(commandManager, StandardApplicationCommandIDs::cut);
            menu.addCommandItem(commandManager, StandardApplicationCommandIDs::copy);
            menu.addCommandItem(commandManager, StandardApplicationCommandIDs::paste);
#if !JUCE_MAC
            menu.addSeparator();
            menu.addCommandItem(commandManager, CommandIDs::Preferences);
#endif
        } else if (menuName == "Help") {
            menu.addCommandItem(commandManager, CommandIDs::HelpContents);
#if !JUCE_MAC
            menu.addSeparator();
            menu.addCommandItem(commandManager, CommandIDs::About);
#endif
        }
        return menu;
    }

    virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex)
    {

    }

    ~coherunceMenuBar()
    {
#if JUCE_MAC
        MenuBarModel::setMacMainMenu(nullptr, nullptr);
#endif
    }

    ScopedPointer<PopupMenu> appleItems;
};


Component* createMainContentComponent();

void coherunceApplication::initialise(const String& commandLine)
{
    mainWindow = new MainWindow(getApplicationName());
    settingsWindow = new SettingsWindow();

    laserThread = new LaserOutputThread();
    laserThread->startThread();

    auto menu = new coherunceMenuBar();
    getApplicationCommandManager().registerAllCommandsForTarget(this);
    menu->initialize();
    mainMenu = menu;
}

void coherunceApplication::shutdown()
{
    laserThread->stopThread(10);

    mainWindow = nullptr;
    settingsWindow = nullptr;
    laserThread = nullptr;
    applicationCommandManager = nullptr;
    sharedAudioDeviceManager = nullptr;
}

void coherunceApplication::systemRequestedQuit()
{
    quit();
}

void coherunceApplication::anotherInstanceStarted (const String& commandLine)
{
}

ApplicationCommandManager& coherunceApplication::getApplicationCommandManager()
{
    if (applicationCommandManager == nullptr)
        applicationCommandManager = new ApplicationCommandManager();

    return *applicationCommandManager;
}

AudioDeviceManager& coherunceApplication::getSharedAudioDeviceManager()
{
    if (sharedAudioDeviceManager == nullptr)
    {
        sharedAudioDeviceManager = new AudioDeviceManager();
        sharedAudioDeviceManager->initialise (2, 2, 0, true, String(), 0);
    }

    return *sharedAudioDeviceManager;
}

SettingsWindow& coherunceApplication::getSettingsWindow()
{
    return *settingsWindow;
}

ApplicationCommandTarget* coherunceApplication::getNextCommandTarget()
{
    return nullptr;
}

void coherunceApplication::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
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
        case CommandIDs::HelpContents:
            result.setInfo(CharPointer_UTF8("coher\xc3\xbcnce Manual"), "Open the user manual", "Help", 0);
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
    }
    JUCEApplication::getCommandInfo(commandID, result);
}

void coherunceApplication::getAllCommands(Array<CommandID>& commands)
{
    commands.add(CommandIDs::About);
    commands.add(CommandIDs::Preferences);
    commands.add(CommandIDs::Open);
    commands.add(CommandIDs::Save);
    commands.add(CommandIDs::HelpContents);
    commands.add(StandardApplicationCommandIDs::undo);
    commands.add(StandardApplicationCommandIDs::redo);
    commands.add(StandardApplicationCommandIDs::cut);
    commands.add(StandardApplicationCommandIDs::copy);
    commands.add(StandardApplicationCommandIDs::paste);

    JUCEApplication::getAllCommands(commands);
}

bool coherunceApplication::perform(const InvocationInfo& info)
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
            // TODO: implement me
            return true;
        case CommandIDs::Save:
            // TODO: implement me
            return true;
        case CommandIDs::HelpContents:
            // TODO: implement me
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

    }

    return JUCEApplication::perform(info);
}


MainWindow::MainWindow(String name)
: DocumentWindow(name, Colours::lightgrey, DocumentWindow::allButtons)
{
    setUsingNativeTitleBar(true);
    setContentOwned (createMainContentComponent(), true);
    setResizable(true, true);

    addKeyListener(getApp()->getApplicationCommandManager().getKeyMappings());

    centreWithSize(getWidth(), getHeight());
    setVisible(true);
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}


START_JUCE_APPLICATION(coherunceApplication)

