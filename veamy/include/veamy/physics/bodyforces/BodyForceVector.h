#ifndef THESIS_BODYFORCEVECTOR_H
#define THESIS_BODYFORCEVECTOR_H

#include <delynoi/models/polygon/Polygon.h>
#include <vector>
#include <veamy/physics/body forces/VeamyBodyForce.h>

class BodyForceVector {
public:
    Eigen::VectorXd computeConstantForceVector(VeamyBodyForce *f, Polygon p, std::vector<Point> points);
    Eigen::VectorXd computeVariableForceVector(VeamyBodyForce *f, Polygon p, std::vector<Point> points);
};


#endif
