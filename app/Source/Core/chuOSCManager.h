/*
  ==============================================================================

    chuOSCManager.h
    Created: 30 Dec 2015 5:14:47pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUOSCMANAGER_H_INCLUDED
#define CHUOSCMANAGER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class chuOSCManager
{
public:
    static void initialize(int port);
    static void deinitialize();
    
    static void setPort(int port);
    static OSCReceiver* getReceiver() { return receiver; }
private:
    static ScopedPointer<OSCReceiver> receiver;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(chuOSCManager)
};



#endif  // CHUOSCMANAGER_H_INCLUDED
