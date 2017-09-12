#ifndef THESIS_VARIABLEBODYFORCE_H
#define THESIS_VARIABLEBODYFORCE_H

#include <veamy/models/dof/DOF.h>
#include <veamy/physics/body forces/VeamyBodyForce.h>
#include <veamy/physics/body forces/BodyForceVector.h>

class VariableBodyForce: public VeamyBodyForce {
public:
     Eigen::VectorXd computeVector(Polygon p, std::vector<Point> points) {
        auto* vector = new BodyForceVector;

        Eigen::VectorXd value = vector->computeVariableForceVector(this, p, points);
        delete vector;

        return value;
    };
};


#endif
