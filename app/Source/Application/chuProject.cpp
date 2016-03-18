/*
  ==============================================================================

    chuProject.cpp
    Created: 9 Mar 2016 7:33:48pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuProject.h"
#include "chuGeneratorManager.h"


chuProject::chuProject()
: data("coherunceProject")
{
    undoManager = new UndoManager();
}

chuProject::~chuProject()
{

}

void chuProject::addGenerator(chuGenerator* gen)
{
    auto genlist = data.getOrCreateChildWithName("generators", nullptr);
    genlist.addChild(gen->getData(), genlist.getNumChildren(), nullptr);
    getGeneratorManager()->addGenerator(gen);
}

void chuProject::deleteGenerator(chuGenerator* gen)
{
    auto genlist = data.getChildWithName("generators");
    if (genlist.isValid())
    {
        genlist.removeChild(gen->getData(), nullptr);
    }
    getGeneratorManager()->deleteGenerator(gen);
}

void chuProject::deserializeGenerators()
{
    auto genList = data.getChildWithName("generators");
    for (int i = 0; i < genList.getNumChildren(); i++)
    {
        auto genData = genList.getChild(i);
        auto genType = genData.getProperty("_type").toString();
        getGeneratorManager()->deserializeGenerator(genType, genData);
    }
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
            deserializeGenerators();
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