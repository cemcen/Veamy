#ifndef DELYNOI_POINTGENERATOR_H
#define DELYNOI_POINTGENERATOR_H

#include <delynoi/models/basic/Point.h>
#include <delynoi/models/polygon/BoundingBox.h>
#include "Functor.h"
#include "delynoi/models/generator/functions/functions.h"
#include <vector>

/*
 * Class in charge of keeping the generator functions and applying them on all points generated.
 */
class PointGenerator {
private:
    /*
     * Function classes that will be used to generate the points values
     */
    Functor* lX;
    Functor* lY;

    /*
     * Variable defining if one or the two function classes are to be used, and the order of the parameters. The variable
     * member can be either x (x is the independent value and y is obtained as f(x)), y (y is the independent value, and
     * x = f(y)), or both (both x and y are obtained as f(x) and f(y))
     */
    functions::independent_variable variable;

    /*
     * Given two coordinates, generates their point using the Function classes.
     * @param x y base coordinates to generate the point
     * @return generated point
     */
    Point result(double x, double y);
public:
    /*
     * Default constructor.
     */
    PointGenerator();

    /*
     * Constructor. Creates a PointGenerator with two Function classes (implicitely, it is assumed that both variables are
     * independant)
     */
    PointGenerator(Functor* lX, Functor* lY);

    /*
     * Constructor. Creates a PointGenerator with one Function class and an independent variable, so to know how the points
     * are to be generater (either x,f(x) or f(y),y)
     */
    PointGenerator(Functor* l, functions::independent_variable variable);

    /*
     * Generates nX x nY points inside a bounding box, using the Function classes to decide each coordinate value.
     * @param vector vector that will contain the generated points
     * @param box bounding box (rectangle) inside which the points will be generated
     * @param nX number of points in the horizontal axis
     * @param nY number of points in the vertical axis
     */
    virtual void generate(std::vector<Point>& vector, BoundingBox box, int nX, int nY);
};

#endif
