#ifndef THESIS_BODYFORCEVECTOR_H
#define THESIS_BODYFORCEVECTOR_H

#include <delynoi/models/polygon/Polygon.h>
#include <vector>
#include <veamy/physics/bodyforces/BodyForce.h>
#include <veamy/lib/Eigen/Dense>

/*
 * Abstract class that models the computation of the part of the load vector related to the body forces
 */
class BodyForceVector {
public:
    /*
     * Computes the body force vector
     * @param f BodyForce applied
     */
    virtual Eigen::VectorXd computeForceVector(BodyForce *f) = 0;
};


#endif
