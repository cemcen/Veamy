#ifndef VEAMY_TRI3CONSTRUCTOR_H
#define VEAMY_TRI3CONSTRUCTOR_H

#include "FeamyElementConstructor.h"

/*
 * Creates the shape functions of a linear triangular element
 */
class Tri3Constructor : public FeamyElementConstructor{
public:
    /*
     * Returns the correct Shape functions associated to the tri3 element
     * @param t geometry of the element
     * @param meshPoints mesh points
     * @return shape functions
     */
    ShapeFunctions* getShapeFunctions(Triangle& t, UniqueList<Point>& meshPoints);
};

#endif