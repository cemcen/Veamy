#ifndef DELYNOI_DELAUNAYTRIANGULATIONGENERATOR_H
#define DELYNOI_DELAUNAYTRIANGULATIONGENERATOR_H

#include "TriangulationGenerator.h"
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleDelaunayGenerator.h>

/*
 * Class that trriangulates a Polygon using its Delaunay triangulation
 */
class DelaunayTriangulationGenerator : public TriangulationGenerator{
public:
    /* Triangulates a polygon.
    * @param p polygon to triangulate
    * @param points list of points instances which the polygon points reference to (most likely, mesh points)
    * @return list of triangles obtained triangulating the polygon
    */
    std::vector<Triangle> triangulate(Polygon p, std::vector<Point> points);
};

#endif