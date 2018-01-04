#ifndef VEAMY_BODYFORCEINTEGRABLE_H
#define VEAMY_BODYFORCEINTEGRABLE_H

#include <veamy/lib/Eigen/Dense>
#include <feamy/integration/IntegrableFunction.h>
#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <veamy/physics/bodyforces/BodyForce.h>

/*
 * Represents the function inside the part of the load vector related to the body force
 */
class BodyForceIntegrable : public IntegrableFunction<Eigen::VectorXd>{
protected:
    /*
     * Shape functions of the element
     */
    ShapeFunctions* N;

    /*
     * Body force applied to the domain
     */
    BodyForce* f;
public:
    /*
     * Constructor
     */
    BodyForceIntegrable(BodyForce* f){
        this->f = f;
    }

    /*
     * Computes the value of the function inside the body force load vector
     * @param p point where the function will be evaluated
     * @return value of the function in p
     */
    virtual Eigen::VectorXd apply(Point p) = 0;

    /* Sets the value of the shape functions of the element
     * @param s shape functions
     */
    void setShapeFunctions(ShapeFunctions* N){
        this->N = N;
    }
};

#endif

