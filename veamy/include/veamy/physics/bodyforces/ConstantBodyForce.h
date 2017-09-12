#ifndef VEAMY_CONSTANTBODYFORCE_H
#define VEAMY_CONSTANTBODYFORCE_H

#include <veamy/physics/body forces/BodyForceVector.h>

class ConstantBodyForce : public VeamyBodyForce{
public:
    Eigen::VectorXd computeVector(Polygon p, std::vector<Point> points) override {
        auto* vector = new BodyForceVector;

        Eigen::VectorXd value = vector->computeConstantForceVector(this, p, points);
        delete vector;

        return value;
    };
};


#endif