#ifndef MESHER_CIRCULARHOLE_H
#define MESHER_CIRCULARHOLE_H

#include <vector>
#include <mesher/models/basic/Point.h>
#include <mesher/models/basic/Segment.h>
#include <mesher/models/polygon/Circle.h>
#include <mesher/models/hole/Hole.h>
#include <mesher/models/polygon/Polygon.h>

class CircularHole: public Hole, public Circle {
private:
    void computeSegments();
public:
    CircularHole(Point p, double r);
};


#endif
