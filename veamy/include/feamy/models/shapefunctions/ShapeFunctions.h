#ifndef VEAMY_SHAPEFUNCTIONS_H
#define VEAMY_SHAPEFUNCTIONS_H

#include <utilities/Pair.h>
#include <delynoi/models/polygon/Triangle.h>

class ShapeFunctions {
private:
    std::vector<Point> p;
    double area;
public:
    ShapeFunctions();
    ShapeFunctions(Triangle elem, std::vector<Point> meshPoints);
    std::vector<double> evaluateShapeFunction(Point point);
    std::vector<Pair<double>> evaluateDerivatives(Point point);
};

#endif