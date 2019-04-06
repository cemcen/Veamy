#ifndef VEAMY_VEAMYPOLYGON_H
#define VEAMY_VEAMYPOLYGON_H

#include <delynoi/models/polygon/Polygon.h>
#include "VeamyTriangle.h"

/*
 * Models a polygon that can be triangulated. Inherits from Delynoi's polygon and uses the triangulation schemes included
 * in that same library
 */
class VeamyPolygon : public Polygon {
public:
    /*
     * Constructor. Creates a VeamyPolygon from a Polygon
     */
    VeamyPolygon(Polygon p);

    /* Triangulates the polygon
     * @param point mesh points
     * @return list of the VeamyTriangles that triangulate the polygon
     */
    std::vector<VeamyTriangle> triangulate(std::vector<Point> &points);
};

#endif