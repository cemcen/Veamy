#ifndef VEAMY_FEAMYTRACTIONVECTOR_H
#define VEAMY_FEAMYTRACTIONVECTOR_H

#include <veamy/physics/traction/TractionVector.h>
#include <delynoi/models/polygon/Triangle.h>
#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <feamy/integration/integrables/BoundaryVectorIntegrable.h>

/*
 * Concrete implementation of TractionVector, which computes the traction vector for linear elasticity for FEM
 */
class FeamyTractionVector : public TractionVector{
private:
    /*
     * Geometric equivalent of the element
     */
    Triangle t;

    /*
     * Mesh points
     */
    std::vector<Point> points;

    /*
     * Neumann or natural constraints of the system
     */
    NaturalConstraints natural;

    /*
     * Shape functions of the element
     */
    ShapeFunctions* N;

    /*
     * Number of gauss points that will be used to integrate
     */
    int nGauss;

    /*
     * Function to integrate (some information is filled as required)
     */
    BoundaryVectorIntegrable* integrable;
public:
    /*
     * Constructor
     */
    FeamyTractionVector(Triangle t, UniqueList<Point> points, ShapeFunctions *N, NaturalConstraints natural, int nGauss,
                        int n_dofs, BoundaryVectorIntegrable *integrable);

    /* Computes the traction load vector related to a segment of an element
     * @param segment segment which traction vector will be computed
     * @return he traction load vector related to the segment
     */
    Eigen::VectorXd computeTractionVector(IndexSegment segment);
};

#endif