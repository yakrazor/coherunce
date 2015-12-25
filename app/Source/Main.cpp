

#include "Main.h"

class coherunceMenuTarget : public ApplicationCommandTarget
{
public:
    // ApplicationCommandTarget interface
    ApplicationCommandTarget* getNextCommandTarget() override;
    void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) override;
    void getAllCommands(Array<CommandID>& commands) override;
    bool perform(const InvocationInfo& info) override;
};

ApplicationCommandTarget* coherunceMenuTarget::getNextCommandTarget()
{
    return nullptr;
}

void coherunceMenuTarget::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
    switch (commandID)
    {
        case CommandIDs::About:
            result.setInfo(CharPointer_UTF8 ("About coher\xc3\xbcnce"), "Version and credits", "General", 0);
            break;
        case CommandIDs::Preferences:
            result.setInfo("Preferences...", "Application and device preferences", "General", 0);
            result.addDefaultKeypress(',', ModifierKeys::commandModifier);
            break;
    }
}

void coherunceMenuTarget::getAllCommands(Array<CommandID>& commands)
{
    commands.add(CommandIDs::About);
    commands.add(CommandIDs::Preferences);
}

bool coherunceMenuTarget::perform(const InvocationInfo& info)
{
    switch (info.commandID)
    {
        case CommandIDs::Preferences:
            getApp()->getSettingsWindow().setVisible(true);
            return true;
    }

    return false;
}


coherunceMenuTarget menuTarget;

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
        appleItems->show();

        MenuBarModel::setMacMainMenu(this, appleItems, "Open Recent");
#endif
    }

    virtual StringArray getMenuBarNames() override
    {
        const char* const names[] = { "Menu 1", "Menu 2", nullptr };

        return StringArray (names);
    }

    virtual PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName)
    {
        PopupMenu menu;
        ApplicationCommandManager* commandManager = &getApp()->getApplicationCommandManager();
        menu.addCommandItem(commandManager, CommandIDs::About);
        return menu;
    }

    virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex)
    {
        // TODO: this line shouldn't be necessary, figure out what's wrong
        menuTarget.perform(menuItemID);
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
    auto menu = new coherunceMenuBar();
    getApplicationCommandManager().registerAllCommandsForTarget(&menuTarget);
    menu->initialize();
    mainMenu = menu;
}

void coherunceApplication::shutdown()
{
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

