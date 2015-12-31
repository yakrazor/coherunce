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

#define PI 3.1415926

struct etherdream *dac_device = nullptr;

#define NUM_POINTS 3000
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

void add_point(etherdream_point* point, int16_t x, int16_t y, uint16_t r, uint16_t g, uint16_t b, uint16_t i)
{
    point->x = x;
    point->y = y;
    point->r = r;
    point->g = g;
    point->b = b;
    point->i = i;
    point->u1 = 0;
    point->u2 = 0;
}

int add_line(etherdream_point* points, int startIndex, int dwellPoints, int numSegments, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t r, uint16_t g, uint16_t b, uint16_t i)
{
    //printf("Line: %d,%d -> %d,%d\n", x1, y1, x2, y2);

    int dx = (x2 - x1) / numSegments;
    int dy = (y2 - y1) / numSegments;
    for (int i = 0; i < dwellPoints; i++)
    {
        add_point(&points[startIndex + i], x1, y1, r, g, b, 0);
    }
    for (int i = 1; i < numSegments; i++)
    {
        add_point(&points[startIndex + dwellPoints + i - 1], x1 + dx * i, y1 + dy * i, r, g, b, i);
    }
    for (int i = 0; i < dwellPoints; i++)
    {
        add_point(&points[startIndex + dwellPoints + numSegments - 1 + i], x2, y2, r, g, b, 0);
    }

    // return next point index
    return startIndex + dwellPoints + numSegments - 1 + dwellPoints;
}

int patterns_to_points(chuThreadQueue<PatternItem>& patterns, etherdream_point* points, int num_points)
{
    int scale = 20000;
    int longestUnbrokenLine = scale / 50;
    int dwellPoints = 15; // this is at each end of a line, so there will actually be 30 per vertex
    int pointIndex = 0;
    int intensity = 32767;
    uint16_t prevItemX = 0;
    uint16_t prevItemY = 0;
    patterns.process_frame([&](chuThreadQueue<PatternItem>::frame_type frame) {
        for (auto& item : frame) {
            if (item.type == PatternType::RegularPolygon) {

                // Find the start point
                float rad = item.rotation * PI/180.0;
                uint16_t origX = (item.origin.x + item.radius * cos(rad)) * scale;
                uint16_t origY = (item.origin.y + item.radius * sin(rad)) * scale;

                // Find the length of the polygon sides and the initial move vector
                int s = 2 * item.radius * sin(PI / item.sides) * scale;
                int move_distance = sqrt(pow(prevItemX - origX, 2) + pow(prevItemY - origY, 2));

                int numMoveSegments = std::max(1, move_distance / longestUnbrokenLine);
                int numSegments = std::max(1, s / longestUnbrokenLine);
                int pointsInPattern = (item.sides + 1) * (numSegments + 1 + dwellPoints * 2) + numMoveSegments;
                if (pointsInPattern + pointIndex > num_points) {
                    continue;
                }

                // move from end of last item to start of this item
                pointIndex = add_line(points, pointIndex, dwellPoints, numMoveSegments, prevItemX, prevItemY, origX, origY, 0, 0, 0, 0);

                uint16_t lastX = origX;
                uint16_t lastY = origY;

                for (int i = 1; i < item.sides; i++) {
                    uint16_t nextX = (item.origin.x + item.radius * cos(2 * PI * i / item.sides + rad)) * scale;
                    uint16_t nextY = (item.origin.y + item.radius * sin(2 * PI * i / item.sides + rad)) * scale;
                    pointIndex = add_line(points, pointIndex, dwellPoints, numSegments, lastX, lastY, nextX, nextY, item.red, item.green, item.blue, intensity);
                    lastX = nextX;
                    lastY = nextY;
                }
                pointIndex = add_line(points, pointIndex, dwellPoints, numSegments, lastX, lastY, origX, origY, item.red, item.green, item.blue, intensity);

                prevItemX = origX;
                prevItemY = origY;
            }
        }

        // Move back to 0,0
        int finalMoveDistance = sqrt(pow(prevItemX, 2) + pow(prevItemY, 2));
        int numFinalMoveSegments = std::max(1, finalMoveDistance / longestUnbrokenLine);
        if (pointIndex + dwellPoints * 2 + numFinalMoveSegments <= num_points)
        {
            pointIndex = add_line(points, pointIndex, dwellPoints, numFinalMoveSegments, prevItemX, prevItemY, 0, 0, 0, 0, 0, 0);
        }

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
    while(true) {
        if (threadShouldExit()) {
            return;
        }
        if (connected) {
            int count = patterns_to_points(patterns, points, NUM_POINTS);
            if (count <= 0) {
                etherdream_stop(dac_device);
                continue;
            } else {
                etherdream_wait_for_ready(dac_device);

                printf("Writing %d points...\n", count);
                log_extents(points, count);
                int res = etherdream_write(dac_device, points, count, 40000, -1);
                if (res != 0) {
                    printf("ERROR: write returned %d\n", res);
                }
            }
        } else {
            wait(250);
        }
    }
}