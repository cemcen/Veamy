#ifndef VEAMY_TRI3CONSTRUCTOR_H
#define VEAMY_TRI3CONSTRUCTOR_H

#include "FeamyElementConstructor.h"

/*
 * Creates a linear triangular element
 */
class Tri3Constructor : public FeamyElementConstructor{
public:
    /*
     * Creates the FEM element.
     * @param conditions conditions of the problem
     * @param t triangle used to create the element
     * @param points mesh points
     * @param out degrees of freedom of the system
     * @return new FEM element
     */
    FeamyElement* createElement(Conditions& conditions, Triangle t, UniqueList<Point>& points, DOFS& out);
};

#endif