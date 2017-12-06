#ifndef VEAMY_VEAMYPOLYGON_H
#define VEAMY_VEAMYPOLYGON_H

#include <delynoi/models/polygon/Polygon.h>
#include "VeamyTriangle.h"

class VeamyPolygon : public Polygon {
private:
    VeamyTriangle getEar(std::vector<Point> points, std::vector<int>& pointList);
public:
    VeamyPolygon(Polygon p);
    std::vector<VeamyTriangle> triangulate(std::vector<Point> points);
};

#endif