#ifndef VEAMY_BOUNDARYVECTORINTEGRABLE_H
#define VEAMY_BOUNDARYVECTORINTEGRABLE_H

#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/geometry/VeamyTriangle.h>
#include "feamy/integration/IntegrableFunction.h"

/*
 * Represents the value inside the elemental load vector (that needs to be integrated) for a given element
 */
class BoundaryVectorIntegrable : public IntegrableFunction<Eigen::VectorXd>{
protected:
    /*
     * Shape functions of the element
     */
    ShapeFunctions* N;

    /*
     * Constraint of the element (load that is imposed)
     */
    Constraint c;

    /*
     * Indexes of the vertices of the element
     */
    std::vector<int> indexes;
public:
    /*
     * Computes the function inside the elemental load vector (that will be integrated)
     * @param p point where the function will be evaluated
     * @return value of the load vector function
     */
    virtual Eigen::VectorXd apply(Point p) = 0;

    /* Sets the value of the shape functions of the element
     * @param s shape functions
     */
    void setShapeFunctions(ShapeFunctions* N){
        this->N = N;
    }

    void setConditions(Constraint c, std::vector<int> indexes){
        this->c = c;
        this->indexes = indexes;
    }
};

#endif