#ifndef DELYNOI_TRIANGULATIONGENERATOR_H
#define DELYNOI_TRIANGULATIONGENERATOR_H

#include <delynoi/models/polygon/Triangle.h>

/*
 * Abstract class that all classes that triangulate a Polygon must implement.
 */
class TriangulationGenerator{
public:
    /* Triangulates a polygon.
     * @param p polygon to triangulate
     * @param points list of points instances which the polygon points reference to (most likely, mesh points)
     * @return list of triangles obtained triangulating the polygon
     */
    virtual std::vector<Triangle> triangulate(Polygon p, std::vector<Point>& points) = 0;
};

#endif