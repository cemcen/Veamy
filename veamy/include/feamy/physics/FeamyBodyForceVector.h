#ifndef VEAMY_FEAMYBODYFORCEVECTOR_H
#define VEAMY_FEAMYBODYFORCEVECTOR_H

#include <veamy/physics/bodyforces/BodyForceVector.h>
#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <veamy/lib/Eigen/Dense>

class FeamyBodyForceVector : public BodyForceVector{
private:
    ShapeFunctions* N;
    std::vector<Point> points;
    Triangle t;
    int nGauss;
public:
    FeamyBodyForceVector(Triangle t, UniqueList<Point> points, ShapeFunctions* N, int nGauss);
    Eigen::VectorXd computeForceVector(BodyForce *f);
};

#endif