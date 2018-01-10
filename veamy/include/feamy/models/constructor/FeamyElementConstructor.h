#ifndef VEAMY_FEMELEMENTCONSTRUCTOR_H
#define VEAMY_FEMELEMENTCONSTRUCTOR_H

#include <feamy/models/FeamyElement.h>

/*
 * Abstract class that encapsulates the creation of the shape functions of a FEM element
 */
class FeamyElementConstructor{
public:
    /*
     * Abstract method. Returns the correct Shape functions associated to each kind of element
     * @param t geometry of the element
     * @param meshPoints mesh points
     * @return shape functions
     */
    virtual ShapeFunctions* getShapeFunctions(Triangle& t, UniqueList<Point>& meshPoints) = 0;
};

#endif