/*
  ==============================================================================

    LaserOutputThread.cpp
    Created: 24 Dec 2015 12:04:33am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include <algorithm>

#include "LaserOutputThread.h"
#include "LaserPointOptimizer.h"

bool logging = false;

LaserOutputThread::LaserOutputThread() : Thread("Laser Output Thread") {
    init();
}

LaserOutputThread::~LaserOutputThread() {
}

bool LaserOutputThread::init() {
    if (outputDriver == nullptr)
    {
        outputDriver = createEtherdreamOutputDriver();
        outputDriver->initialize();
        wait(1200);
    }

    if (outputDevices.size() == 0)
    {
        int cc = outputDriver->getDeviceCount();
        if (!cc) {
            printf("No DACs found.\n");
            return false;
        }

        for (int i = 0; i < outputDriver->getDeviceCount(); i++) {
            printf("Connecting...\n");
            auto outputDevice = outputDriver->connectToDevice(i);
            
            if (outputDevice == nullptr)
            {
                printf("Could not connect to DAC!\n");
                return false;
            }
            outputDevices.add(outputDevice);
        }
        
    }

    return true;
}

void LaserOutputThread::disableOutput()
{
    outputDriver->disableOutput();
}

void LaserOutputThread::enableOutput()
{
    outputDriver->enableOutput();
}

void LaserOutputThread::run() {

    int frameCount = 0;
    double clock = Time::getMillisecondCounterHiRes();
    int count = 0;

    while(true)
    {
        if (threadShouldExit())
        {
            return;
        }
        if (outputDriver == nullptr || outputDevices.size() == 0) {
            wait(250);
            init();
        }
        if (outputDriver && outputDriver->isOutputEnabled() && outputDevices.size() > 0)
        {
            LaserPointOptimizer optimizer(laserConfig, outputDevices[0]->getState());
            optimizer.fillBufferFromFrame(outputBuffer);

            for (auto outputDevice : outputDevices) {
                outputDevice->setRedDelay(getLaserConfig().redDelay->getValue());
                outputDevice->setGreenDelay(getLaserConfig().greenDelay->getValue());
                outputDevice->setBlueDelay(getLaserConfig().blueDelay->getValue());

                count = outputBuffer.getPointCount();
                if (count <= 0) {
                    outputDevice->stop();
                    continue;
                }
                else
                {
                    if (outputDevice->waitForDeviceReady())
                    {

                        if (!outputDevice->writeToDevice(laserConfig, outputBuffer))
                        {
                            printf("ERROR: write failed\n");
                        }

                        frameCount++;
                        if (frameCount == 20) {
                            double now = Time::getMillisecondCounterHiRes();
                            double delta = now - clock;

                            stats.framesPerSecond = 20000/delta;
                            stats.pointsPerFrame = count;

                            // TODO: move this to UI
                            printf("Points: %d FPS: %f\n", stats.pointsPerFrame, stats.framesPerSecond);

                            frameCount = 0;
                            clock = now;
                        }
                    }
                }
            }
        }
    }
}