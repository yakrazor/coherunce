/*
  ==============================================================================

    chuProject.h
    Created: 9 Mar 2016 7:33:48pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUPROJECT_H_INCLUDED
#define CHUPROJECT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "chuGenerator.h"

class chuProject
{
public:
    chuProject();
    ~chuProject();

    void addGenerator(chuGenerator* gen);
    void deleteGenerator(chuGenerator* gen);

    void deserialize();
    
    void loadFromFile(String filePath);
    void loadFromFile(File file);

    void saveToFile();
    void saveToFile(File file);

    String filePath;
    ValueTree data;

    ScopedPointer<UndoManager> undoManager;
};



#endif  // CHUPROJECT_H_INCLUDED
