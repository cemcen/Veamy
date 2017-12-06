#ifndef THESIS_BODYFORCEVECTOR_H
#define THESIS_BODYFORCEVECTOR_H

#include <delynoi/models/polygon/Polygon.h>
#include <vector>
#include <veamy/physics/bodyforces/BodyForce.h>
#include <veamy/lib/Eigen/Dense>

class BodyForceVector {
public:
    virtual Eigen::VectorXd computeForceVector(BodyForce *f) = 0;
};


#endif
