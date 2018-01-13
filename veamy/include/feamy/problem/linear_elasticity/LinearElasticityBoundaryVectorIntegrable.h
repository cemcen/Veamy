#ifndef VEAMY_LINEARELASTICITYBOUNDARYVECTORINTEGRABLE_H
#define VEAMY_LINEARELASTICITYBOUNDARYVECTORINTEGRABLE_H

#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/geometry/VeamyTriangle.h>
#include "feamy/integration/IntegrableFunction.h"

/*
 * Represents the value inside the elemental load vector (that needs to be integrated) for a given element for
 * the linear elasticity problem
 */
class LinearElasticityBoundaryVectorIntegrable : public BoundaryVectorIntegrable{
public:
    /*
     * Constructor
     */
    LinearElasticityBoundaryVectorIntegrable(){}

    /*
     * Computes the function inside the elemental load vector (that will be integrated)
     * @param p point where the function will be evaluated
     * @return value of the load vector function
     */
    Eigen::VectorXd apply(Point p){
        std::vector<double> Ni = this->N->evaluateShapeFunctionCartesian(p);
        Eigen::MatrixXd N;
        N = Eigen::MatrixXd::Zero(2,2*this->indexes.size());

        Eigen::VectorXd t;
        t = Eigen::VectorXd::Zero(2);

        for (int i = 0; i < this->indexes.size(); ++i) {
            N(0,2*i) = Ni[indexes[i]];
            N(1,2*i+1) = Ni[indexes[i]];

            t(i) += c.getValue(p)*c.isAffected(i);
        }

        return N.transpose()*t;
    }



};

#endif