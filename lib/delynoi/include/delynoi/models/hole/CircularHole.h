#ifndef DELYNOI_CIRCULARHOLE_H
#define DELYNOI_CIRCULARHOLE_H

#include <vector>
#include <delynoi/models/basic/Point.h>
#include <delynoi/models/basic/Segment.h>
#include <delynoi/models/polygon/Circle.h>
#include <delynoi/models/hole/Hole.h>
#include <delynoi/models/polygon/Polygon.h>


/*
 * Class modeling a circular hole.
 */
class CircularHole: public Hole, public Circle {
private:
    /*
     * Calculates the segments of the hole based on the radius and center of the circle.
     */
    void computeSegments();
public:
    /*
     * Constructor.
     */
    CircularHole(Point p, double r);
};


#endif
