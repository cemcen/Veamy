#ifndef VEAMY_SHAPEFUNCTIONS_H
#define VEAMY_SHAPEFUNCTIONS_H

#include <utilities/Pair.h>
#include <delynoi/models/polygon/Triangle.h>

class ShapeFunctions {
protected:
    std::vector<Point> p;
    double area;
public:
    ShapeFunctions();
    ShapeFunctions(Triangle elem, std::vector<Point> meshPoints);
    virtual std::vector<double> evaluateShapeFunction(Point point) = 0;
    virtual std::vector<double> evaluateShapeFunctionCartesian(Point point) = 0;
    virtual std::vector<Pair<double>> evaluateDerivatives(Point point) = 0;
    virtual Point evaluateRealPoint(Point p)=0;
    int numberOfShapeFunctions();
};

#endif