#ifndef DELYNOI_EARTRIANGULATIONGENERATOR_H
#define DELYNOI_EARTRIANGULATIONGENERATOR_H

#include "TriangulationGenerator.h"

class EarTriangulationGenerator : public TriangulationGenerator {
private:
    Triangle getEar(std::vector<Point> points, std::vector<int>& pointList);
public:
    std::vector<Triangle> triangulate(Polygon p, std::vector<Point> points);
};

#endif