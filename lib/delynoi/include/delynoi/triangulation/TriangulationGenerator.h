#ifndef DELYNOI_TRIANGULATIONGENERATOR_H
#define DELYNOI_TRIANGULATIONGENERATOR_H

#include <delynoi/models/polygon/Triangle.h>

class TriangulationGenerator{
public:
    virtual std::vector<Triangle> triangulate(Polygon p, std::vector<Point> points) = 0;
};

#endif