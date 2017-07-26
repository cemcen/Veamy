#ifndef THESIS_BODYFORCEVECTOR_H
#define THESIS_BODYFORCEVECTOR_H

#include <mesher/models/polygon/Polygon.h>
#include <vector>
#include <veamy/physics/BodyForce.h>

class BodyForceVector {
public:
    Eigen::VectorXd computeConstantForceVector(BodyForce *f, Polygon p, std::vector<Point> points);
    Eigen::VectorXd computeVariableForceVector(BodyForce *f, Polygon p, std::vector<Point> points);
};


#endif
