#ifndef VEAMY_BODYFORCEINTEGRABLE_H
#define VEAMY_BODYFORCEINTEGRABLE_H

#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <veamy/physics/bodyforces/BodyForce.h>
#include <veamy/lib/Eigen/Dense>
#include "IntegrableFunction.h"

class BodyForceIntegrable : public IntegrableFunction<Eigen::VectorXd>{
private:
    ShapeFunctions* N;
    BodyForce* f;
public:
    BodyForceIntegrable(ShapeFunctions* shape, BodyForce* f){
        this->N = shape;
        this->f = f;
    }

    Eigen::VectorXd apply(Point p, int index){
        int n = this->N->numberOfShapeFunctions();
        Eigen::MatrixXd Ne;
        Ne = Eigen::MatrixXd::Zero(2,2*n);

        std::vector<double> Ni = N->evaluateShapeFunction(p);
        for (int i = 0; i < n; ++i) {
            Ne(0,2*i) = Ni[2*i];
            Ne(1,2*i+1) = Ni[2*i+1];
        }

        Eigen::VectorXd b;
        b = Eigen::VectorXd::Zero(2);

        Point real = this->N->evaluateRealPoint(p);


        b(0) = f->getX()->apply(real.getX(), real.getY(), 0, Polygon());
        b(1) = f->getY()->apply(real.getX(), real.getY(), 0, Polygon());

        return Ne.transpose()*b;
    }

};

#endif