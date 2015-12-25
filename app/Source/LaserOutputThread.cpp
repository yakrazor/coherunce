/*
  ==============================================================================

    LaserOutputThread.cpp
    Created: 24 Dec 2015 12:04:33am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "LaserOutputThread.h"
#include <etherdream.h>
#include "etherdream_test.h"


struct etherdream *dac_device = nullptr;

#define NUM_POINTS 600
struct etherdream_point points[NUM_POINTS];


LaserOutputThread::LaserOutputThread() : Thread("Laser Output Thread") {
   connected = false;
   if (init()) {
       connected = true;
   }
}

LaserOutputThread::~LaserOutputThread() {
}

bool LaserOutputThread::init() {
    etherdream_lib_start();
    wait(1200);

	int cc = etherdream_dac_count();
	if (!cc) {
		printf("No DACs found.\n");
		return false;
	}

	dac_device = etherdream_get(0);

	printf("Connecting...\n");
    if (etherdream_connect(dac_device) < 0) {
        printf("Could not connect to DAC!\n");
        return false;
    } else {
        return true;
    }
}

void LaserOutputThread::run() {
    while(true) {
        if (threadShouldExit()) {
            return;
        }
        if (connected) {
            fill_circle(points, NUM_POINTS, 0, 0);
            etherdream_wait_for_ready(dac_device);
            int res = etherdream_write(dac_device, points, NUM_POINTS, 30000, 1);
            if (res != 0) {
                printf("write returned %d\n", res);
            }
        } else {
            wait(500);
        }
    }
}