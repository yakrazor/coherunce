/*
  ==============================================================================

    chuProject.cpp
    Created: 9 Mar 2016 7:33:48pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuProject.h"

chuProject::chuProject()
: data("coherunceProject")
{
    undoManager = new UndoManager();

    data.addChild(ValueTree("generators"), 0, nullptr);
}

chuProject::~chuProject()
{

}

void chuProject::loadFromFile(String filePath)
{
    File file(filePath);
    loadFromFile(file);
}

void chuProject::loadFromFile(File file)
{
    filePath = file.getFullPathName();
    XmlDocument doc(file);

    auto xmlElement = doc.getDocumentElement();
    if (xmlElement) {
        auto newData = ValueTree::fromXml(*xmlElement);
        if (newData != ValueTree::invalid) {
            data = newData;
        }
        delete xmlElement;
    } else {
        // todo: error
    }
}

void chuProject::saveToFile()
{
    saveToFile(File(filePath));
}

void chuProject::saveToFile(File file)
{
    String xml = data.toXmlString();
    file.create();
    file.replaceWithText(xml);
}