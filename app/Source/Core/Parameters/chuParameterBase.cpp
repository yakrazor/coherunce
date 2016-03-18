/*
  ==============================================================================

    chuParameterBase.cpp
    Created: 2 Jan 2016 11:47:13am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuParameterBase.h"
#include "chuApplication.h"
#include "chuOSCManager.h"

chuParameterOptions chuParameterOptions::Default;

#include <map>
#include <utility>

class NamingHelper
{
public:

    String getUniqueNumberedName(String base)
    {
        auto iter = numberingMap.find(base);
        if (iter == numberingMap.end())
        {
            iter = numberingMap.insert(std::make_pair(base, 0)).first;
        }
        return base + String(++iter->second);
    }

    void saveNumberedName(String name)
    {
        String permittedCharacters = "1234567890";
        String base = String::empty;
        String trailing = String::empty;

        for (int index = name.length() - 1; index >= 0; index--)
        {
            if (!permittedCharacters.containsChar(name[index]))
            {
                base = name.substring(0, index + 1);
                trailing = name.substring(index + 1);
                break;
            }
        }

        if (trailing.isNotEmpty() && base.isNotEmpty())
        {
            int number = trailing.getIntValue();
            auto iter = numberingMap.find(base);
            if (iter == numberingMap.end())
            {
                iter = numberingMap.insert(std::make_pair(base, number)).first;
            }
            else
            {
                if (number > numberingMap[base])
                {
                    numberingMap[base] = number;
                }
            }
        }
    }

protected:
    std::map<String, int> numberingMap;
};

NamingHelper namingHelper;

chuParameter::chuParameter(const String& name, const chuParameterOptions& paramOptions)
: options(paramOptions)
{
    data = ValueTree("parameter");
    data.setProperty("name", name, nullptr);
}

chuParameterProvider::chuParameterProvider(const String& typeName, ValueTree source)
{
    data = source;
    data.setProperty("_type", typeName, nullptr);
    if (!data.hasProperty("name"))
    {
        data.setProperty("name", namingHelper.getUniqueNumberedName(typeName), nullptr);
    }
    else
    {
        namingHelper.saveNumberedName(data.getProperty("name"));
    }
}

chuParameterProvider::~chuParameterProvider()
{
    deregisterOSCAddresses();
}

void chuParameterProvider::getParamList(std::vector<chuParameter*>& params) const
{
    for (auto iter = parameters.begin(); iter != parameters.end(); iter++)
    {
        params.push_back(*iter);
    }
}

const String chuParameterProvider::getType() const
{
    if (data.isValid())
    {
        return data.getProperty("_type");
    } else {
        return "";
    }
}

const String chuParameterProvider::getName() const
{
    if (data.isValid())
    {
        return data.getProperty("name");
    } else {
        return "";
    }
}

void chuParameterProvider::setName(String name)
{
    if (data.isValid())
    {
        data.setProperty("name", name, nullptr);
    }
}

void chuParameterProvider::addParameter(chuParameter* newParam)
{
    parameters.add(newParam);
    auto saved = data.getChildWithProperty("name", newParam->getName());
    if (saved.isValid())
    {
        newParam->deserialize(saved);
        data.removeChild(saved, nullptr);
    }
    data.addChild(newParam->data, data.getNumChildren(), nullptr);

    if (getOSCRoot().isNotEmpty())
    {
        newParam->listenAtOSCAddress(getOSCRoot());
    }
}

void chuParameterProvider::remapOSCAddresses()
{
    std::vector<chuParameter*> params;
    getParamList(params);
    for (auto& param : params)
    {
        param->listenAtOSCAddress(getOSCRoot());
    }
}

void chuParameterProvider::deregisterOSCAddresses()
{
    if (chuOSCManager::getReceiver())
    {
        std::vector<chuParameter*> params;
        getParamList(params);
        for (auto& param : params)
        {
            chuOSCManager::getReceiver()->removeListener(param);
        }
    }
}

void chuParameter::listenAtOSCAddress(const String& prefix)
{
    chuOSCManager::getReceiver()->removeListener(this);
    String fullAddress = prefix + "/param/" + getName();
    fullAddress = fullAddress.replaceCharacters(" #*,?[]{}", "_");
    printf("[OSC] Registering OSC address %s\n", fullAddress.toRawUTF8());
    chuOSCManager::getReceiver()->addListener(this, fullAddress);
}

PropertyPanel* chuParameterProvider::createPanel() const
{
    Array<PropertyComponent*> propertyComponents;
    std::vector<chuParameter*> params;

    getParamList(params);
    for (auto& param : params)
    {
        if (!param->getOptions().isUserVisible)
            continue;
        auto pc = param->createComponent();
        pc->setColour(PropertyComponent::backgroundColourId, Colours::transparentBlack);
        propertyComponents.add(pc);
    }

    String displayName = getName();
    String type = getType();
    if (!displayName.contains(type))
    {
        displayName += " (" + type + ")";
    }

    auto panel = new PropertyPanel();
    panel->addSection(displayName + " Parameters", propertyComponents);
    return panel;
}



