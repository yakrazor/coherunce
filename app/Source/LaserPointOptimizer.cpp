/*
  ==============================================================================

    LaserPointOptimizer.cpp
    Created: 6 Jan 2016 12:27:36am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "LaserPointOptimizer.h"
#include "LaserConfig.h"
#include "LaserOutputBuffer.h"
#include "LaserState.h"

#define PI 3.1415926

LaserPointOptimizer::LaserPointOptimizer(const LaserConfig& _config, const LaserState& _state)
: pointIndex(0), config(_config), state(_state)
{
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

void LaserPointOptimizer::addLine(ildaPoint* points, int dwellOffPoints, int dwellOnPoints, int numSegments, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t r, uint16_t g, uint16_t b, uint16_t i)
{

    int dx = (x2 - x1) / numSegments;
    int dy = (y2 - y1) / numSegments;
    for (int i = 0; i < dwellOffPoints; i++)
    {
        add_point(&points[pointIndex++], x1, y1, 0, 0, 0, 0);
    }
    for (int i = 0; i < dwellOnPoints; i++)
    {
        add_point(&points[pointIndex++], x1, y1, r, g, b, i);
    }
    for (int i = 0; i <= numSegments; i++)
    {
        add_point(&points[pointIndex++], x1 + dx * i, y1 + dy * i, r, g, b, i);
    }
    for (int i = 0; i < dwellOnPoints; i++)
    {
        add_point(&points[pointIndex++], x2, y2, r, g, b, i);
    }
    for (int i = 0; i < dwellOffPoints; i++)
    {
        add_point(&points[pointIndex++], x2, y2, 0, 0, 0, 0);
    }
}

void LaserPointOptimizer::fillBufferFromFrame(LaserOutputBuffer& buffer)
{
    pointIndex = 0;

    int scale = config.ildaXMax;
    int longestUnbrokenLine = config.longestUnbrokenLine.getValue();
    int internalShapeDwellPoints = config.internalDwellPoints.getValue();
    int dwellOffPoints = config.dwellOffPoints.getValue();
    int dwellOnPoints = config.dwellOnPoints.getValue();
    int intensityMax = config.ildaIntensityMax;

    uint16_t intensity = intensityMax * std::max(0.0f, std::min(config.globalIntensity.getValue(), 1.0f));

    int16_t prevItemX = state.currentPoint.x;
    int16_t prevItemY = state.currentPoint.y;

    buffer.getPatternQueue().process_frame([&](LaserOutputBuffer::PatternQueue::frame_type frame) {
        for (auto& item : frame) {

            // clamp input point
            if (item.origin.x < -1.0) { item.origin.x = -1.0; }
            if (item.origin.x > 1.0)  { item.origin.x = 1.0; }
            if (item.origin.y < -1.0) { item.origin.y = -1.0; }
            if (item.origin.y > 1.0)  { item.origin.y = 1.0; }

            if (item.type == PatternType::Polyline) {
                if (item.points.size() == 0)
                {
                    continue;
                }

                int16_t ptX = item.points[0].x * scale;
                int16_t ptY = item.points[0].y * scale;

                int move_distance = sqrt(pow(prevItemX - ptX, 2) + pow(prevItemY - ptY, 2));
                int numMoveSegments = std::max(1, move_distance / longestUnbrokenLine);

                // move from end of last item to start of this item
                addLine(buffer.points, dwellOffPoints, dwellOnPoints, numMoveSegments, prevItemX, prevItemY, ptX, ptY, 0, 0, 0, 0);

                prevItemX = ptX;
                prevItemY = ptY;

                for (auto& itemPt : item.points)
                {
                    int16_t ptX = itemPt.x * scale;
                    int16_t ptY = itemPt.y * scale;

                    int distance = sqrt(pow(prevItemX - ptX, 2) + pow(prevItemY - ptY, 2));
                    int numSegments = std::max(1, distance / longestUnbrokenLine);
                    addLine(buffer.points, 0, internalShapeDwellPoints, numSegments, prevItemX, prevItemY, ptX, ptY, item.red, item.green, item.blue, intensity);

                    prevItemX = ptX;
                    prevItemY = ptY;
                }

            }
            else if (item.type == PatternType::RegularPolygon) {

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
                if (pointsInPattern + pointIndex > LaserOutputBuffer::maxPoints) {
                    continue;
                }

                // move from end of last item to start of this item
                addLine(buffer.points, dwellOffPoints, dwellOnPoints, numMoveSegments, prevItemX, prevItemY, origX, origY, 0, 0, 0, 0);

                int16_t lastX = origX;
                int16_t lastY = origY;

                for (int i = 0; i < item.sides; i++) {
                    int16_t nextX = (item.origin.x + item.radius * cos(2 * PI * i / item.sides + rad)) * scale;
                    int16_t nextY = (item.origin.y + item.radius * sin(2 * PI * i / item.sides + rad)) * scale;
                    addLine(buffer.points, 0, internalShapeDwellPoints, numSegments, lastX, lastY, nextX, nextY, item.red, item.green, item.blue, intensity);
                    lastX = nextX;
                    lastY = nextY;
                }
                addLine(buffer.points, 0, internalShapeDwellPoints, numSegments, lastX, lastY, origX, origY, item.red, item.green, item.blue, intensity);

                prevItemX = origX;
                prevItemY = origY;
            }
        }

        buffer.pointCount = pointIndex > 0 ? pointIndex : 0;

    });
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