#ifndef VEAMY_TRI3SHAPEFUNCTIONS_H
#define VEAMY_TRI3SHAPEFUNCTIONS_H

#include "ShapeFunctions.h"

class Tri3ShapeFunctions : public ShapeFunctions {
public:
    Tri3ShapeFunctions(Triangle t, std::vector<Point> points);
    std::vector<double> evaluateShapeFunction(Point point);
    std::vector<Pair<double>> evaluateDerivatives(Point point);
    Point evaluateRealPoint(Point point);
};

#endif