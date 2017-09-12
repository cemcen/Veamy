#ifndef VEAMY_VEMBODYFORCE_H
#define VEAMY_VEMBODYFORCE_H

#include <veamy/lib/Eigen/Dense>
#include <veamy/physics/body forces/VeamyBodyForce.h>
#include <veamy/physics/body forces/BodyForce.h>

class VeamyBodyForce: public BodyForce{
public:
    virtual Eigen::VectorXd computeVector(Polygon p, std::vector<Point> points) = 0;
};

#endif