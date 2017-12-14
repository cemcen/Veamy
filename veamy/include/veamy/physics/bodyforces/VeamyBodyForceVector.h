#ifndef VEAMY_VEAMYBODYFORCEVECTOR_H
#define VEAMY_VEAMYBODYFORCEVECTOR_H

#include <veamy/physics/bodyforces/BodyForceVector.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/utilities/veamy_functions.h>

/*
 * Concrete implementation of the BodyForceVector class, computing the elemental load vector as done in VEM
 */
class VeamyBodyForceVector : public BodyForceVector{
private:
    /*
     *  Polygon related to the VEM element
     */
    Polygon polygon;

    /*
     * Points of the mesh
     */
    std::vector<Point> points;
public:
    /*
     * Constructor
     */
    VeamyBodyForceVector(Polygon p, UniqueList<Point> points);

    /*
     * Computes the elemental body force vector for VEM given an applied body force
     * @param f BodyForce applied
     */
    Eigen::VectorXd computeForceVector(BodyForce *f);
};

#endif