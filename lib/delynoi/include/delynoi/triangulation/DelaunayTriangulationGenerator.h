#ifndef DELYNOI_DELAUNAYTRIANGULATIONGENERATOR_H
#define DELYNOI_DELAUNAYTRIANGULATIONGENERATOR_H

#include "TriangulationGenerator.h"
#include <delynoi/models/Region.h>
#include <delynoi/voronoi/TriangleDelaunayGenerator.h>

class DelaunayTriangulationGenerator : public TriangulationGenerator{
public:
    std::vector<Triangle> triangulate(Polygon p, std::vector<Point> points);
};

#endif