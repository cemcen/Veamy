#ifndef VEAMY_INTEGRABLEFUNCTION_H
#define VEAMY_INTEGRABLEFUNCTION_H

#include <delynoi/models/basic/Point.h>
#include <veamy/geometry/VeamyTriangle.h>

/*
 * Abstract class that encapsulates the behaviour of all functions that can be numerically integrated
 */
template <typename S>
class IntegrableFunction{
public:
    /*
     * Method that represents the function. All concrete implementations of IntegrableFunction must implement this
     * method.
     * @param p point where the function is to be evaluated
     * @return value of the function at p
     */
    virtual S apply(Point p) = 0;

    /*
     * Method that represents the function, receiving the triangle that contains the point where the function will
     * be evaluated
     * @param p point where the function is to be evaluated
     * @param container triangle that contains the point
     * @return value of the function at p
     */
    virtual S apply(Point p, const VeamyTriangle& container){
        return this->apply(p);
    }
};

#endif