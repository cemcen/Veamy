#ifndef THESIS_VARIABLEBODYFORCE_H
#define THESIS_VARIABLEBODYFORCE_H

#include <veamy/models/dof/DOF.h>
#include <veamy/physics/BodyForce.h>
#include <veamy/physics/BodyForceVector.h>

class VariableBodyForce: public BodyForce {
public:
     Pair<double> computeVector(Polygon p, std::vector<Point> points) override {
        auto* vector = new BodyForceVector;

        Pair<double> value = vector->computeVariableForceVector(this, p, points);
        delete vector;

        return value;
    };
};


#endif
