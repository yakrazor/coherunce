/*
  ==============================================================================

    LaserOutputDriver.h
    Created: 5 Jan 2016 10:04:12pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef LASEROUTPUTDRIVER_H_INCLUDED
#define LASEROUTPUTDRIVER_H_INCLUDED

class LaserConfig;
class LaserOutputBuffer;
class LaserState;

class LaserOutputDevice
{
public:
    virtual ~LaserOutputDevice() {}

    virtual bool waitForDeviceReady() = 0;
    virtual bool writeToDevice(LaserConfig& laserConfig, LaserOutputBuffer& buffer) = 0;
    virtual void stop() = 0;

    virtual void setRedDelay(int delay) = 0;
    virtual void setGreenDelay(int delay) = 0;
    virtual void setBlueDelay(int delay) = 0;

    virtual LaserState& getState() = 0;
};

class LaserOutputDriver
{
public:
    virtual ~LaserOutputDriver() {}

    virtual void initialize() = 0;
    virtual int getDeviceCount() = 0;
    virtual LaserOutputDevice* connectToDevice(int index) = 0;

    virtual void disableOutput() = 0;
    virtual void enableOutput() = 0;
    virtual bool isOutputEnabled() = 0;
};

LaserOutputDriver* createEtherdreamOutputDriver();


#endif  // LASEROUTPUTDEVICE_H_INCLUDED
