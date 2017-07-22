#ifndef VEAMY_CONSTANTBODYFORCE_H
#define VEAMY_CONSTANTBODYFORCE_H

#include <veamy/physics/BodyForceVector.h>

class ConstantBodyForce : public BodyForce{
public:
    Pair<double> computeVector(Polygon p, std::vector<Point> points) override {
        auto* vector = new BodyForceVector;

        Pair<double> value = vector->computeConstantForceVector(this, p, points);
        delete vector;

        return value;
    };
};


#endif