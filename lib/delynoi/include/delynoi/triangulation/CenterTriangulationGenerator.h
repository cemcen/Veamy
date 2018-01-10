#ifndef VEAMY_CENTERTRIANGULATIONGENERATOR_H
#define VEAMY_CENTERTRIANGULATIONGENERATOR_H

#include "TriangulationGenerator.h"

class CenterTriangulationGenerator : public TriangulationGenerator{
public:
    std::vector<Triangle> triangulate(Polygon p, std::vector<Point>& points);
};

#endif