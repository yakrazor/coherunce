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

void add_point(ildaPoint* point, int16_t x, int16_t y, const Colour& colour, uint16_t i)
{
    point->x = x;
    point->y = y;
    point->r = colour.getRed() << 8;
    point->g = colour.getGreen() << 8;
    point->b = colour.getBlue() << 8;
    point->i = i;
    point->u1 = 0;
    point->u2 = 0;
}

// Cohen-Sutherland implementation from Wikipedia
// TODO: replace with more efficient choice

typedef int OutCode;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Compute the bit code for a point (x, y) using the clip rectangle
// bounded diagonally by (xmin, ymin), and (xmax, ymax)

const int xmin = -1;
const int xmax = 1;
const int ymin = -1;
const int ymax = 1;

OutCode ComputeOutCode(double x, double y)
{
    OutCode code;

    code = INSIDE;          // initialised as being inside of clip window

    if (x < xmin)           // to the left of clip window
        code |= LEFT;
    else if (x > xmax)      // to the right of clip window
        code |= RIGHT;
    if (y < ymin)           // below the clip window
        code |= BOTTOM;
    else if (y > ymax)      // above the clip window
        code |= TOP;

    return code;
}

// Cohen–Sutherland clipping algorithm clips a line from
// P0 = (x0, y0) to P1 = (x1, y1) against a rectangle with
// diagonal from (xmin, ymin) to (xmax, ymax).
bool CohenSutherlandLineClip(float& x0, float& y0, float& x1, float& y1)
{
    // compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
    OutCode outcode0 = ComputeOutCode(x0, y0);
    OutCode outcode1 = ComputeOutCode(x1, y1);
    bool accept = false;

    while (true) {
        if (!(outcode0 | outcode1)) { // Bitwise OR is 0. Trivially accept and get out of loop
            accept = true;
            break;
        } else if (outcode0 & outcode1) { // Bitwise AND is not 0. Trivially reject and get out of loop
            break;
        } else {
            // failed both tests, so calculate the line segment to clip
            // from an outside point to an intersection with clip edge
            double x, y;

            // At least one endpoint is outside the clip rectangle; pick it.
            OutCode outcodeOut = outcode0 ? outcode0 : outcode1;

            // Now find the intersection point;
            // use formulas y = y0 + slope * (x - x0), x = x0 + (1 / slope) * (y - y0)
            if (outcodeOut & TOP) {           // point is above the clip rectangle
                x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                y = ymax;
            } else if (outcodeOut & BOTTOM) { // point is below the clip rectangle
                x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                y = ymin;
            } else if (outcodeOut & RIGHT) {  // point is to the right of clip rectangle
                y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
                x = xmax;
            } else if (outcodeOut & LEFT) {   // point is to the left of clip rectangle
                y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
                x = xmin;
            }

            // Now we move outside point to intersection point to clip
            // and get ready for next pass.
            if (outcodeOut == outcode0) {
                x0 = x;
                y0 = y;
                outcode0 = ComputeOutCode(x0, y0);
            } else {
                x1 = x;
                y1 = y;
                outcode1 = ComputeOutCode(x1, y1);
            }
        }
    }

    return accept;
}


bool LaserPointOptimizer::addLine(ildaPoint* points, float fx1, float fy1, float fx2, float fy2, const Colour& startColour, const Colour& endColour, uint16_t i)
{
    int xScale = config.ildaXMax * (config.flipHorizontal->getValue() ? -1 : 1);
    int yScale = config.ildaYMax * (config.flipVertical->getValue() ? -1 : 1);

    int longestUnbrokenLine = config.longestUnbrokenLine->getValue();
    int dwellOffPoints = config.dwellOffPoints->getValue();
    int dwellOnPoints = config.dwellOnPoints->getValue();

    int x1 = fx1 * xScale;
    int y1 = fy1 * yScale;
    int x2 = fx2 * xScale;
    int y2 = fy2 * yScale;

    int distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    int numSegments = std::max(1, distance / longestUnbrokenLine);

    int dx = (x2 - x1) / numSegments;
    int dy = (y2 - y1) / numSegments;

    for (int i = 0; i < dwellOffPoints; i++)
    {
        add_point(&points[pointIndex++], x1, y1, Colours::black, 0);
    }
    for (int i = 0; i < dwellOnPoints; i++)
    {
        add_point(&points[pointIndex++], x1, y1, startColour, i);
    }
    for (int i = 0; i <= numSegments; i++)
    {
        Colour interpColour = startColour.interpolatedWith(endColour, i / (numSegments * 1.0));
        add_point(&points[pointIndex++], x1 + dx * i, y1 + dy * i, interpColour, i);
    }
    for (int i = 0; i < dwellOnPoints; i++)
    {
        add_point(&points[pointIndex++], x2, y2, endColour, i);
    }
    for (int i = 0; i < dwellOffPoints; i++)
    {
        add_point(&points[pointIndex++], x2, y2, Colours::black, 0);
    }

    return true;
}

void LaserPointOptimizer::fillBufferFromFrame(LaserOutputBuffer& buffer)
{
    pointIndex = 0;

    int intensityMax = config.ildaIntensityMax;

    uint16_t intensity = intensityMax * std::max(0.0f, std::min(config.globalIntensity->getValue(), 1.0f));

    int xScale = config.ildaXMax * (config.flipHorizontal->getValue() ? -1 : 1);
    int yScale = config.ildaYMax * (config.flipVertical->getValue() ? -1 : 1);

    float currentX = state.currentPoint.x / (xScale * 1.0);
    float currentY = state.currentPoint.y / (yScale * 1.0);

    buffer.getPatternQueue().process_frame([&](LaserOutputBuffer::PatternQueue::frame_type frame) {
        for (auto& item : frame) {

            if (item.type == PatternType::RegularPolygon) {

                // Convert to polyline
                item.type = PatternType::Polyline;

                // Find the start point
                float rad = item.rotation * PI/180.0;
                float x = (item.origin.x + item.radius * cos(rad));
                float y = (item.origin.y + item.radius * sin(rad));
                item.polyline.addPoint(Vector2f(x, y), item.colour);

                for (int i = 1; i < item.sides + 1; i++) {
                    x = (item.origin.x + item.radius * cos(2 * PI * i / item.sides + rad));
                    y = (item.origin.y + item.radius * sin(2 * PI * i / item.sides + rad));
                    item.polyline.addPoint(Vector2f(x, y), item.colour);
                }
            }

            if (item.type == PatternType::Polyline) {

                auto& vertices = item.polyline.vertices;
                if (vertices.size() == 0)
                {
                    continue;
                }

                for (int i = 0; i < vertices.size() - 1; i++)
                {
                    float lineStartX = vertices[i].x;
                    float lineStartY = vertices[i].y;
                    float lineEndX = vertices[i+1].x;
                    float lineEndY = vertices[i+1].y;

                    // Potentially clip the line endpoints, skipping if completely offscreen
                    if (!CohenSutherlandLineClip(lineStartX, lineStartY, lineEndX, lineEndY))
                    {
                        continue;
                    }

                    // If we're not already at the start, do a blank move to the start of this line
                    if (lineStartX != currentX || lineStartY != currentY)
                    {
                        addLine(buffer.points, currentX, currentY, lineStartX, lineStartY, Colours::black, Colours::black, 0);
                    }

                    const Colour& startColour = item.polyline.colours[i];
                    const Colour& endColour = item.polyline.colours[i + 1];

                    addLine(buffer.points, lineStartX, lineStartY, lineEndX, lineEndY, startColour, endColour, intensity);

                    currentX = lineEndX;
                    currentY = lineEndY;
                }

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