/*
  ==============================================================================

    chuMenuBar.cpp
    Created: 25 Dec 2015 5:14:08pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuMenuBar.h"
#include "chuApplication.h"

chuMenuBar::chuMenuBar()
{
    setApplicationCommandManagerToWatch(&getApp()->getApplicationCommandManager());
}

void chuMenuBar::initialize()
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

StringArray chuMenuBar::getMenuBarNames()
{
    const char* const names[] = { "File", "Edit", "Help", nullptr };
    return StringArray (names);
}

PopupMenu chuMenuBar::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
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
        menu.addCommandItem(commandManager, CommandIDs::CloseWindow);
        menu.addSeparator();
        menu.addCommandItem(commandManager, CommandIDs::Save);
        menu.addCommandItem(commandManager, CommandIDs::SaveAs);
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

void chuMenuBar::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{

}

chuMenuBar::~chuMenuBar()
{
#if JUCE_MAC
    MenuBarModel::setMacMainMenu(nullptr, nullptr);
#endif
}
