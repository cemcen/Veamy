#ifndef VEAMY_FEMELEMENTCONSTRUCTOR_H
#define VEAMY_FEMELEMENTCONSTRUCTOR_H

#include <feamy/models/FeamyElement.h>

/*
 * Abstract class that encapsulates the creation of a FEM element (which can be of different shapes and orders)
 */
class FeamyElementConstructor{
public:
    /*
     * Abstract method. Creates a FEM element.
     * @param conditions conditions of the problem
     * @param t triangle used to create the element
     * @param points mesh points
     * @param out degrees of freedom of the system
     * @return new FEM element
     */
    virtual FeamyElement* createElement(Conditions& conditions, Triangle t, UniqueList<Point>& points, DOFS& out) = 0;
};

#endif