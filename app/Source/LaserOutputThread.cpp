/*
  ==============================================================================

    LaserOutputThread.cpp
    Created: 24 Dec 2015 12:04:33am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include <algorithm>

#include "LaserOutputThread.h"
#include <etherdream.h>
#include "etherdream_test.h"

#define PI 3.1415926

struct etherdream *dac_device = nullptr;

#define NUM_POINTS 3500
struct etherdream_point points[NUM_POINTS];

bool logging = false;


LaserOutputThread::LaserOutputThread() : Thread("Laser Output Thread") {
    connected = false;
    enabled = false;
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

void LaserOutputThread::disableOutput()
{
    if (connected)
    {
        etherdream_stop(dac_device);
    }
    enabled = false;
}

void LaserOutputThread::enableOutput()
{
    enabled = true;
}

void add_point(etherdream_point* point, int16_t x, int16_t y, uint16_t r, uint16_t g, uint16_t b, uint16_t i, int diodeGalvOffset)
{
    point->x = x;
    point->y = y;
    (point + diodeGalvOffset)->r = r;
    (point + diodeGalvOffset)->g = g;
    (point + diodeGalvOffset)->b = b;
    (point + diodeGalvOffset)->i = i;
    point->u1 = 0;
    point->u2 = 0;
}

int add_line(etherdream_point* points, int startIndex, int dwellOffPoints, int dwellOnPoints, int numSegments, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t r, uint16_t g, uint16_t b, uint16_t i, int diodeGalvOffset)
{
    //printf("Line: %d,%d -> %d,%d\n", x1, y1, x2, y2);

    int dx = (x2 - x1) / numSegments;
    int dy = (y2 - y1) / numSegments;
    for (int i = 0; i < dwellOffPoints; i++)
    {
        add_point(&points[startIndex++], x1, y1, 0, 0, 0, 0, diodeGalvOffset);
    }
    for (int i = 0; i < dwellOnPoints; i++)
    {
        add_point(&points[startIndex++], x1, y1, r, g, b, i, diodeGalvOffset);
    }
    for (int i = 0; i <= numSegments; i++)
    {
        add_point(&points[startIndex++], x1 + dx * i, y1 + dy * i, r, g, b, i, diodeGalvOffset);
    }
    for (int i = 0; i < dwellOnPoints; i++)
    {
        add_point(&points[startIndex++], x2, y2, r, g, b, i, diodeGalvOffset);
    }
    for (int i = 0; i < dwellOffPoints; i++)
    {
        add_point(&points[startIndex++], x2, y2, 0, 0, 0, 0, diodeGalvOffset);
    }

    // return next point index
    return startIndex;
}

int patterns_to_points(uint16_t lastFrameX, uint16_t lastFrameY, float globalIntensity, chuThreadQueue<PatternItem>& patterns, etherdream_point* points, int num_points)
{
    int scale = 24000;
    int longestUnbrokenLine = scale / 25;
    int internalShapeDwellPoints = 1;
    int dwellOffPoints = 10;
    int dwellOnPoints = 2;
    int diodeGalvOffset = 12;
    int pointIndex = diodeGalvOffset < 0 ? diodeGalvOffset : 0;
    int intensityMax = 32767;

    uint16_t intensity = intensityMax * std::max(0.0f, std::min(globalIntensity, 1.0f));

    int16_t prevItemX = lastFrameX;
    int16_t prevItemY = lastFrameY;
    patterns.process_frame([&](chuThreadQueue<PatternItem>::frame_type frame) {
        for (auto& item : frame) {
            if (item.type == PatternType::RegularPolygon) {

                // clamp input point
                if (item.origin.x < -1.0) { item.origin.x = -1.0; }
                if (item.origin.x > 1.0)  { item.origin.x = 1.0; }
                if (item.origin.y < -1.0) { item.origin.y = -1.0; }
                if (item.origin.y > 1.0)  { item.origin.y = 1.0; }

                // Find the start point
                float rad = item.rotation * PI/180.0;
                int16_t origX = (item.origin.x + item.radius * cos(rad)) * scale;
                int16_t origY = (item.origin.y + item.radius * sin(rad)) * scale;

                // Find the length of the polygon sides and the initial move vector
                int s = 2 * item.radius * sin(PI / item.sides) * scale;
                int move_distance = sqrt(pow(prevItemX - origX, 2) + pow(prevItemY - origY, 2));

                int numMoveSegments = std::max(1, move_distance / longestUnbrokenLine);
                int numSegments = std::max(1, s / longestUnbrokenLine);
                int pointsInPattern = (item.sides + 1) * (numSegments + 1 + 2 * internalShapeDwellPoints) + numMoveSegments + dwellOnPoints + dwellOffPoints;
                if (pointsInPattern + pointIndex > num_points) {
                    continue;
                }

                // move from end of last item to start of this item
                pointIndex = add_line(points, pointIndex, dwellOffPoints, dwellOnPoints, numMoveSegments, prevItemX, prevItemY, origX, origY, 0, 0, 0, 0, diodeGalvOffset);

                int16_t lastX = origX;
                int16_t lastY = origY;

                for (int i = 0; i < item.sides; i++) {
                    int16_t nextX = (item.origin.x + item.radius * cos(2 * PI * i / item.sides + rad)) * scale;
                    int16_t nextY = (item.origin.y + item.radius * sin(2 * PI * i / item.sides + rad)) * scale;
                    pointIndex = add_line(points, pointIndex, 0, internalShapeDwellPoints, numSegments, lastX, lastY, nextX, nextY, item.red, item.green, item.blue, intensity, diodeGalvOffset);
                    lastX = nextX;
                    lastY = nextY;
                }
                pointIndex = add_line(points, pointIndex, 0, internalShapeDwellPoints, numSegments, lastX, lastY, origX, origY, item.red, item.green, item.blue, intensity, diodeGalvOffset);

                prevItemX = origX;
                prevItemY = origY;
            }
        }
/*
        // Move back to 0,0
        int finalMoveDistance = sqrt(pow(prevItemX, 2) + pow(prevItemY, 2));
        int numFinalMoveSegments = std::max(1, finalMoveDistance / longestUnbrokenLine);
        if (pointIndex + dwellPoints * 2 + numFinalMoveSegments <= num_points)
        {
            pointIndex = add_line(points, pointIndex, dwellPoints, numFinalMoveSegments, prevItemX, prevItemY, 0, 0, 0, 0, 0, 0);
        }
*/

        for (int i = 0; i < diodeGalvOffset; i++)
            add_point(&points[pointIndex++], prevItemX, prevItemY, 0, 0, 0, 0, diodeGalvOffset);

        if (logging)
            printf("Generated %d DAC points from %lu pattern items\n", pointIndex, frame.size());
    });
    return pointIndex > 0 ? pointIndex : 0;
}

void log_extents(etherdream_point* points, int count)
{
    int minX = INT16_MAX;
    int minY = INT16_MAX;
    int maxX = INT16_MIN;
    int maxY = INT16_MIN;
    for (int i = 0; i < count; i++) {
        if (points[i].x < minX) { minX = points[i].x; }
        if (points[i].x > maxX) { maxX = points[i].x; }
        if (points[i].y < minY) { minY = points[i].y; }
        if (points[i].y > maxY) { maxY = points[i].y; }
    }
    printf("Extents: X = %d..%d, Y = %d..%d\n", minX, maxY, minY, maxY);
}

void LaserOutputThread::run() {
    int16_t lastFrameX = 0;
    int16_t lastFrameY = 0;
    int frameCount = 0;
    double clock = Time::getMillisecondCounterHiRes();
    int count = 0;

    while(true) {
        if (threadShouldExit()) {
            return;
        }
        if (!connected) {
            wait(250);
        }
        if (connected && !enabled) {
            etherdream_stop(dac_device);
            continue;
        }
        if (connected && enabled) {
            count = patterns_to_points(lastFrameX, lastFrameY, globalIntensity, patterns, points, NUM_POINTS);
            if (count <= 0) {
                etherdream_stop(dac_device);
                lastFrameX = 0;
                lastFrameY = 0;
                continue;
            } else {
                etherdream_wait_for_ready(dac_device);

                if (logging)
                {
                    printf("Writing %d points...\n", count);
                    log_extents(points, count);
                }

                int res = etherdream_write(dac_device, points, count, 10000, count < 200 ? -1 : 1);
                if (res != 0) {
                    printf("ERROR: write returned %d\n", res);
                }

                lastFrameX = points[count - 1].x;
                lastFrameY = points[count - 1].y;

                frameCount++;
                if (frameCount == 20) {
                    double now = Time::getMillisecondCounterHiRes();
                    double delta = now - clock;

                    printf("Points: %d FPS: %f\n", count, 20000/delta);
                    frameCount = 0;
                    clock = now;
                }
            }
        }
    }
}