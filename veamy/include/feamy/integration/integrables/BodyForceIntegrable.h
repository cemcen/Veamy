#ifndef VEAMY_BODYFORCEINTEGRABLE_H
#define VEAMY_BODYFORCEINTEGRABLE_H

#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <veamy/physics/bodyforces/BodyForce.h>
#include <veamy/lib/Eigen/Dense>
#include "IntegrableFunction.h"

/*
 * Represents the function inside the part of the load vector related to the body force
 */
class BodyForceIntegrable : public IntegrableFunction<Eigen::VectorXd>{
private:
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
    BodyForceIntegrable(ShapeFunctions* shape, BodyForce* f){
        this->N = shape;
        this->f = f;
    }

    /*
     * Computes the value of the function inside the body force load vector
     * @param p point where the function will be evaluated
     * @return value of the function in p
     */
    Eigen::VectorXd apply(Point p){
        int n = this->N->numberOfShapeFunctions();
        int dofs = f->numberOfComponents();

        Eigen::MatrixXd Ne;
        Ne = Eigen::MatrixXd::Zero(dofs,dofs*n);

        std::vector<double> Ni = N->evaluateShapeFunction(p);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < dofs; ++j) {
                Ne(j, dofs*i+j) = Ni[i];
            }
        }

        Eigen::VectorXd b;
        b = Eigen::VectorXd::Zero(dofs);

        Point real = this->N->evaluateRealPoint(p);
        std::vector<FunctionComputable*> components = f->getComponents();

        for (int k = 0; k < dofs; ++k) {
            b(dofs) = components[k]->apply(real.getX(), real.getY(), 0, Polygon());
        }

        return Ne.transpose()*b;
    }

};

#endif