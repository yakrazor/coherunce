/*
  ==============================================================================

    chuOSCManager.cpp
    Created: 30 Dec 2015 5:14:47pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuOSCManager.h"
#define LOG_OSC 0

ScopedPointer<OSCReceiver> chuOSCManager::receiver = nullptr;

class chuOSCMessageLogger : public OSCReceiver::Listener<OSCReceiver::MessageLoopCallback>
{
public:
    virtual void oscMessageReceived(const OSCMessage& message) override
    {
        printf("[OSC] Received %s with %d args\n",
               message.getAddressPattern().toString().toRawUTF8(), message.size());
    }
};

chuOSCMessageLogger theLogger;

void chuOSCManager::initialize(int port)
{
    if (!receiver)
    {
        receiver = new OSCReceiver();
        if (LOG_OSC)
        {
            receiver->addListener(&theLogger);
        }
    }
    setPort(port);
}

void chuOSCManager::setPort(int port)
{
    if (receiver)
    {
        receiver->connect(port);
    }
}