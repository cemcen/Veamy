#ifndef DELYNOI_CIRCULARHOLE_H
#define DELYNOI_CIRCULARHOLE_H

#include <vector>
#include <delynoi/models/basic/Point.h>
#include <delynoi/models/basic/Segment.h>
#include <delynoi/models/polygon/Circle.h>
#include <delynoi/models/hole/Hole.h>
#include <delynoi/models/polygon/Polygon.h>

class CircularHole: public Hole, public Circle {
private:
    void computeSegments();
public:
    CircularHole(Point p, double r);
};


#endif
