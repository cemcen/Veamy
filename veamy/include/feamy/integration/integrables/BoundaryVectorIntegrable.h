#ifndef VEAMY_BOUNDARYVECTORINTEGRABLE_H
#define VEAMY_BOUNDARYVECTORINTEGRABLE_H

#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/geometry/VeamyTriangle.h>
#include "IntegrableFunction.h"

/*
 * Represents the value inside the elemental load vector (that needs to be integrated) for a given element
 */
class BoundaryVectorIntegrable : public IntegrableFunction<Eigen::VectorXd>{
private:
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
     * Constructor
     */
    BoundaryVectorIntegrable(Constraint c, ShapeFunctions* N, std::vector<int> indexes){
        this->N = N;
        this->c = c;
        this->indexes = indexes;
    }

    /*
     * Computes the function inside the elemental load vector (that will be integrated)
     * @param p point where the function will be evaluated
     * @return value of the load vector function
     */
    Eigen::VectorXd apply(Point p){
        std::vector<double> Ni = this->N->evaluateShapeFunctionCartesian(p);
        Eigen::MatrixXd N;
        N = Eigen::MatrixXd::Zero(2,2*this->indexes.size());

        for (int i = 0; i < 2; ++i) {
            N(0,2*i) = Ni[indexes[i]];
            N(1,2*i+1) = Ni[indexes[i]];
        }

        Eigen::VectorXd t;
        t = Eigen::VectorXd::Zero(2);

        t(0) = c.getValue(p)*c.isAffected(DOF::Axis::x);
        t(1) += c.getValue(p)*c.isAffected(DOF::Axis::y);

        return N.transpose()*t;
    }

};

#endif