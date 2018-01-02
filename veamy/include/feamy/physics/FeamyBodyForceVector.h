#ifndef VEAMY_FEAMYBODYFORCEVECTOR_H
#define VEAMY_FEAMYBODYFORCEVECTOR_H

#include <veamy/physics/bodyforces/BodyForceVector.h>
#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <veamy/lib/Eigen/Dense>
#include <feamy/integration/integrables/BodyForceIntegrable.h>

/*
 * Concrete implementation of the BodyForceVector class, computing the elemental load vector as done in FEM
 */
class FeamyBodyForceVector : public BodyForceVector{
private:
    /*
     * Shape functions of the element
     */
    ShapeFunctions* N;

    /*
     * Points of the element
     */
    std::vector<Point> points;

    /*
     * Geometric representation of the element
     */
    Triangle t;

    /*
     * Number of gauss points used for the numerical integration
     */
    int nGauss;

    /*
     * Function to integrate
     */
    BodyForceIntegrable* integrable;
public:
    /*
     * Constructor
     */
    FeamyBodyForceVector(Triangle t, UniqueList<Point> points, ShapeFunctions *N, int nGauss,
                         BodyForceIntegrable *integrable);

    /*
     * Computes the elemental body force vector for FEM given an applied body force
     * @param f BodyForce applied
     */
    Eigen::VectorXd computeForceVector(BodyForce *f);
};

#endif