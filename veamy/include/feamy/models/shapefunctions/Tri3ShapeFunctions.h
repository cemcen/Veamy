#ifndef VEAMY_TRI3SHAPEFUNCTIONS_H
#define VEAMY_TRI3SHAPEFUNCTIONS_H

#include "ShapeFunctions.h"

/*
 * Represents the shape functions of a linear triangular element
 */
class Tri3ShapeFunctions : public ShapeFunctions {
public:
    /*
     * Constructor
     */
    Tri3ShapeFunctions(Triangle t, std::vector<Point> points);

    /* Evaluates the shape functions on a point (in isoparametric coordinates)
     * @param point point where the functions will be evaluated
     * @return value of the shape functions at p
     */
    std::vector<double> evaluateShapeFunction(Point point);

    /* Evaluates the derivatives of the shape functions on a point (in isoparametric coordinates)
     * @param point point where the functions will be evaluated
     * @return value of the derivatives of the shape functions at p
     */
    std::vector<Pair<double>> evaluateDerivatives(Point point);

    /* Returns the cartesian version of an isoparametric point
     * @param p isoparametric point to transform
     * @return cartesian version of p
     */
    Point evaluateRealPoint(Point point);

    /* Evaluates the shape functions on a point (in cartesian coordinates)
     * @param point point where the functions will be evaluated
     * @return value of the shape functions at p
     */
    std::vector<double> evaluateShapeFunctionCartesian(Point point);
};

#endif