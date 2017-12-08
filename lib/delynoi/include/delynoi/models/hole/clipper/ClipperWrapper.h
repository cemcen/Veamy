#ifndef DELYNOI_CLIPPERWRAPPER_H
#define DELYNOI_CLIPPERWRAPPER_H

#include <delynoi/models/hole/clipper/lib/clipper.hpp>
#include <delynoi/models/basic/Point.h>
#include <delynoi/models/polygon/Polygon.h>

/*
 * Class that transform the polygon and region information of the Delynoi library to a format accepted by Clipper,
 * computing the intersection as required.
 */
class ClipperWrapper {
private:
    /*
     * Scales a point (which has double precision coordinates) to an integer, using the given scale.
     */
    static ClipperLib::IntPoint scalePoint(Point point, int maxScale);
public:
    /* Computes the intersection between two polygons using Clipper
     * @param parent list of points defining the parent (bigger) polygon
     * @param child list of points defining the child polygon (the one that clips)
     * @param maxScale scale used to transform double points to integers
     */
    static ClipperLib::Paths polyIntersection(std::vector<Point> parent, std::vector<Point> child, int maxScale);
};


#endif
