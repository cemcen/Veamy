#ifndef VEAMY_BOUNDARYVECTORINTEGRABLE_H
#define VEAMY_BOUNDARYVECTORINTEGRABLE_H

#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/geometry/VeamyTriangle.h>
#include "IntegrableFunction.h"

class BoundaryVectorIntegrable : public IntegrableFunction<Eigen::VectorXd>{
private:
    ShapeFunctions* N;
    Constraint c;
    std::vector<int> indexes;
public:
    BoundaryVectorIntegrable(Constraint c, ShapeFunctions* N, std::vector<int> indexes){
        this->N = N;
        this->c = c;
        this->indexes = indexes;
    }

    Eigen::VectorXd apply(Point p){
        std::vector<double> Ni = this->N->evaluateShapeFunction(p);
        Eigen::MatrixXd N(2,2);

        for (int i = 0; i < 2; ++i) {
            N(0,2*i) = Ni[indexes[i]];
            N(1,2*i+1) = Ni[indexes[i]];
        }

        Eigen::VectorXd t;
        t = Eigen::VectorXd::Zero(2);

        Point real = this->N->evaluateRealPoint(p);

        t(0) = c.getValue(real)*c.isAffected(DOF::Axis::x);
        t(1) += c.getValue(real)*c.isAffected(DOF::Axis::y);

        return N.transpose()*t;
    }

};

#endif