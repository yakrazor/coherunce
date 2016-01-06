/*
  ==============================================================================

    LaserOutputThread.cpp
    Created: 24 Dec 2015 12:04:33am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include <algorithm>

#include "LaserOutputThread.h"

#define PI 3.1415926

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

void add_point(ildaPoint* point, int16_t x, int16_t y, uint16_t r, uint16_t g, uint16_t b, uint16_t i)
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

int add_line(ildaPoint* points, int startIndex, int dwellOffPoints, int dwellOnPoints, int numSegments, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t r, uint16_t g, uint16_t b, uint16_t i)
{
    //printf("Line: %d,%d -> %d,%d\n", x1, y1, x2, y2);

    int dx = (x2 - x1) / numSegments;
    int dy = (y2 - y1) / numSegments;
    for (int i = 0; i < dwellOffPoints; i++)
    {
        add_point(&points[startIndex++], x1, y1, 0, 0, 0, 0);
    }
    for (int i = 0; i < dwellOnPoints; i++)
    {
        add_point(&points[startIndex++], x1, y1, r, g, b, i);
    }
    for (int i = 0; i <= numSegments; i++)
    {
        add_point(&points[startIndex++], x1 + dx * i, y1 + dy * i, r, g, b, i);
    }
    for (int i = 0; i < dwellOnPoints; i++)
    {
        add_point(&points[startIndex++], x2, y2, r, g, b, i);
    }
    for (int i = 0; i < dwellOffPoints; i++)
    {
        add_point(&points[startIndex++], x2, y2, 0, 0, 0, 0);
    }

    // return next point index
    return startIndex;
}

int patterns_to_points(const LaserConfig& config, uint16_t lastFrameX, uint16_t lastFrameY, float globalIntensity, chuThreadQueue<PatternItem>& patterns, ildaPoint* points, int num_points)
{
    int scale = config.ildaXMax;
    int longestUnbrokenLine = config.longestUnbrokenLine.getValue();
    int internalShapeDwellPoints = config.internalDwellPoints.getValue();
    int dwellOffPoints = config.dwellOffPoints.getValue();
    int dwellOnPoints = config.dwellOnPoints.getValue();
    int intensityMax = config.ildaIntensityMax;

    int pointIndex = 0;

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
                pointIndex = add_line(points, pointIndex, dwellOffPoints, dwellOnPoints, numMoveSegments, prevItemX, prevItemY, origX, origY, 0, 0, 0, 0);

                int16_t lastX = origX;
                int16_t lastY = origY;

                for (int i = 0; i < item.sides; i++) {
                    int16_t nextX = (item.origin.x + item.radius * cos(2 * PI * i / item.sides + rad)) * scale;
                    int16_t nextY = (item.origin.y + item.radius * sin(2 * PI * i / item.sides + rad)) * scale;
                    pointIndex = add_line(points, pointIndex, 0, internalShapeDwellPoints, numSegments, lastX, lastY, nextX, nextY, item.red, item.green, item.blue, intensity);
                    lastX = nextX;
                    lastY = nextY;
                }
                pointIndex = add_line(points, pointIndex, 0, internalShapeDwellPoints, numSegments, lastX, lastY, origX, origY, item.red, item.green, item.blue, intensity);

                prevItemX = origX;
                prevItemY = origY;
            }
        }

        if (logging)
            printf("Generated %d DAC points from %lu pattern items\n", pointIndex, frame.size());
    });
    return pointIndex > 0 ? pointIndex : 0;
}

void log_extents(ildaPoint* points, int count)
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
            // TODO: move patterns_to_points into LaserOutputBuffer class
            //outputBuffer.processFrame();
            //count = outputBuffer.getPointCount();

            count = patterns_to_points(laserConfig, lastFrameX, lastFrameY, globalIntensity, outputBuffer.getPatternQueue(), outputBuffer.getPoints(), NUM_POINTS);
            outputBuffer.setPointCount(count);

            if (count <= 0) {
                outputDevice->stop();
                
                lastFrameX = 0;
                lastFrameY = 0;
                continue;
            }
            else
            {
                outputDevice->waitForDeviceReady();

                if (!outputDevice->writeToDevice(laserConfig, outputBuffer))
                {
                    printf("ERROR: write failed\n");
                }

                lastFrameX = outputBuffer.getPoints()[count - 1].x;
                lastFrameY = outputBuffer.getPoints()[count - 1].y;

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