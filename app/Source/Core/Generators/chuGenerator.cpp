/*
  ==============================================================================

    chuGenerator.cpp
    Created: 30 Dec 2015 1:32:56pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuGenerator.h"
#include "chuOSCManager.h"


chuGenerator::chuGenerator(String generatorName) : name(generatorName), active(false)
{
    init();
};

void chuGenerator::setOSCAddress(const String& addr)
{
    std::vector<chuParameter*> params;
    getParamList(params);
    for (auto& param : params)
    {
        if (chuOSCManager::getReceiver())
        {
            chuOSCManager::getReceiver()->removeListener(param);
            chuOSCManager::getReceiver()->addListener(param, addr + "/param/" + param->getName());
        }
    }
}

