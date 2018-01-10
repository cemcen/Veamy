#ifndef VEAMY_LINEARELASTICITYBODYFORCEINTEGRABLE_H
#define VEAMY_LINEARELASTICITYBODYFORCEINTEGRABLE_H


#include <feamy/integration/integrables/BodyForceIntegrable.h>
#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <veamy/physics/bodyforces/BodyForce.h>

/*
 * Represents the function inside the part of the load vector related to the body force, specifically for the linear
 * elasticity problem
 */
class LinearElasticityBodyForceIntegrable : public BodyForceIntegrable{
public:
    /*
     * Constructor
     */
    LinearElasticityBodyForceIntegrable(BodyForce* f) : BodyForceIntegrable(f){}

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
            b(k) = components[k]->apply(real.getX(), real.getY(), 0, Polygon());
        }

        return Ne.transpose()*b;
    }

};

#endif