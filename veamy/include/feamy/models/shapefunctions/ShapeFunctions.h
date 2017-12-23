#ifndef VEAMY_SHAPEFUNCTIONS_H
#define VEAMY_SHAPEFUNCTIONS_H

#include <utilities/Pair.h>
#include <delynoi/models/polygon/Triangle.h>

/*
 * Abstract class that represent the shape functions of a FEM element
 */
class ShapeFunctions {
protected:
    /*
     * Points of the element
     */
    std::vector<Point> p;

    /*
     * Area of the element
     */
    double area;
public:
    /*
     * Default constructor
     */
    ShapeFunctions();

    /*
     * Constructor
     */
    ShapeFunctions(Triangle elem, std::vector<Point> meshPoints);

    /* Evaluates the shape functions on a point (in isoparametric coordinates)
     * @param point point where the functions will be evaluated
     * @return value of the shape functions at p
     */
    virtual std::vector<double> evaluateShapeFunction(Point point) = 0;

    /* Evaluates the shape functions on a point (in cartesian coordinates)
     * @param point point where the functions will be evaluated
     * @return value of the shape functions at p
     */
    virtual std::vector<double> evaluateShapeFunctionCartesian(Point point) = 0;

    /* Evaluates the derivatives of the shape functions on a point (in isoparametric coordinates)
     * @param point point where the functions will be evaluated
     * @return value of the derivatives of the shape functions at p
     */
    virtual std::vector<Pair<double>> evaluateDerivatives(Point point) = 0;

    /* Returns the cartesian version of an isoparametric point
     * @param p isoparametric point to transform
     * @return cartesian version of p
     */
    virtual Point evaluateRealPoint(Point p)=0;

    /*
     * @return number of shape functions in this set
     */
    int numberOfShapeFunctions();
};

#endif