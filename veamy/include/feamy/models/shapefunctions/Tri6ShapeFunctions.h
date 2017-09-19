#ifndef VEAMY_TRI6SHAPEFUNCTIONS_H
#define VEAMY_TRI6SHAPEFUNCTIONS_H

#include "ShapeFunctions.h"

class Tri6ShapeFunctions : public ShapeFunctions {
public:
    Tri6ShapeFunctions(Triangle t, std::vector<Point> points);
    std::vector<double> evaluateShapeFunction(Point point);
    std::vector<Pair<double>> evaluateDerivatives(Point point);
    Point evaluateRealPoint(Point point);
    std::vector<double> evaluateShapeFunctionCartesian(Point point);
};

#endif