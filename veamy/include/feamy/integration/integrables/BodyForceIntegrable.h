#ifndef VEAMY_BODYFORCEINTEGRABLE_H
#define VEAMY_BODYFORCEINTEGRABLE_H

#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <veamy/physics/bodyforces/BodyForce.h>

class BodyForceIntegrable {
private:
    ShapeFunctions* N;
    BodyForce* f;
public:
    BodyForceIntegrable(ShapeFunctions* shape, BodyForce* f){
        this->N = shape;
        this->f = f;
    }

    Eigen::VectorXd function(double x, double y){
        Eigen::MatrixXd Ne;
        Ne = Eigen::MatrixXd::Zero(2,6);

        std::vector<double> Ni = N->evaluateShapeFunction(Point(x,y));
        for (int i = 0; i < 3; ++i) {
            Ne(0,2*i) = Ni[2*i];
            Ne(1,2*i+1) = Ni[2*i+1];
        }

        Eigen::VectorXd b;
        b = Eigen::VectorXd::Zero(2);

        b(0) = f->applyX(x, y);
        b(1) = f->applyY(x, y);

        return Ne.transpose()*b;
    }

};

#endif