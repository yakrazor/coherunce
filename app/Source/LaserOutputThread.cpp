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

    if (outputDevice == nullptr)
    {
        int cc = outputDriver->getDeviceCount();
        if (!cc) {
            printf("No DACs found.\n");
            return false;
        }

        printf("Connecting...\n");
        outputDevice = outputDriver->connectToDevice(0);

        if (outputDevice == nullptr)
        {
            printf("Could not connect to DAC!\n");
            return false;
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
        if (outputDriver == nullptr || outputDevice == nullptr) {
            wait(250);
            init();
        }
        if (outputDriver && outputDriver->isOutputEnabled() && outputDevice)
        {
            outputDevice->setRedDelay(getLaserConfig().redDelay.getValue());
            outputDevice->setGreenDelay(getLaserConfig().greenDelay.getValue());
            outputDevice->setBlueDelay(getLaserConfig().blueDelay.getValue());

            LaserPointOptimizer optimizer(laserConfig, outputDevice->getState());
            optimizer.fillBufferFromFrame(outputBuffer);

            count = outputBuffer.getPointCount();
            if (count <= 0) {
                outputDevice->stop();
                continue;
            }
            else
            {
                outputDevice->waitForDeviceReady();

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