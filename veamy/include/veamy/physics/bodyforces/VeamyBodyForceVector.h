#ifndef VEAMY_VEAMYBODYFORCEVECTOR_H
#define VEAMY_VEAMYBODYFORCEVECTOR_H

#include <veamy/physics/bodyforces/BodyForceVector.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/utilities/veamy_functions.h>

class VeamyBodyForceVector : public BodyForceVector{
private:
    Polygon polygon;
    std::vector<Point> points;
public:
    VeamyBodyForceVector(Polygon p, UniqueList<Point> points);
    Eigen::VectorXd computeForceVector(BodyForce *f);
};

#endif