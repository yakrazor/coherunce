/*
  ==============================================================================

    LaserOutputDevice.cpp
    Created: 5 Jan 2016 10:04:12pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "LaserOutputDriver.h"
#include "LaserOutputBuffer.h"
#include "LaserConfig.h"

#include <etherdream.h>
#include "etherdream_test.h"


class EtherdreamOutputDevice : public LaserOutputDevice
{
public:
    EtherdreamOutputDevice(LaserOutputDriver* driver, struct etherdream* device)
    : thisDevice(device), parentDriver(driver)
    {
    }

    virtual ~EtherdreamOutputDevice() override
    {
    }

    virtual void waitForDeviceReady() override
    {
        etherdream_wait_for_ready(thisDevice);
    }

    virtual bool writeToDevice(LaserConfig& laserConfig, LaserOutputBuffer& buffer) override
    {
        if (!parentDriver || !parentDriver->isOutputEnabled())
        {
            etherdream_stop(thisDevice);
            return false;
        }

        int count = buffer.getPointCount();
        int res = etherdream_write(thisDevice,
                                   (etherdream_point*)buffer.getPoints(),
                                   count,
                                   laserConfig.pointsPerSecond.getValue(), count < 600 ? -1 : 1);
        if (res != 0)
        {
            return false;
        }

        return true;
    }

    virtual void stop() override
    {
        etherdream_stop(thisDevice);
    }

private:
    struct etherdream* thisDevice;
    LaserOutputDriver* parentDriver;
};

class EtherdreamOutputDriver : public LaserOutputDriver
{
public:
    EtherdreamOutputDriver()
    : outputEnabled(false)
    {
    }

    virtual ~EtherdreamOutputDriver()
    {
    }

    virtual void initialize() override
    {
        etherdream_lib_start();
    }

    virtual int getDeviceCount() override
    {
        return etherdream_dac_count();
    }

    virtual LaserOutputDevice* connectToDevice(int index) override
    {
        auto device = etherdream_get(index);
        if (etherdream_connect(device) < 0)
        {
            return nullptr;
        }
        
        return new EtherdreamOutputDevice(this, device);
    }

    virtual void disableOutput() override
    {
        outputEnabled = false;
        for (int i = 0; i < etherdream_dac_count(); i++)
        {
            auto device = etherdream_get(i);
            if (device)
            {
                etherdream_stop(device);
            }
        }
    }

    virtual void enableOutput() override
    {
        outputEnabled = true;
    }

    virtual bool isOutputEnabled() override
    {
        return outputEnabled;
    }

private:
    bool outputEnabled;
};

LaserOutputDriver* createEtherdreamOutputDriver()
{
    return new EtherdreamOutputDriver();
}



