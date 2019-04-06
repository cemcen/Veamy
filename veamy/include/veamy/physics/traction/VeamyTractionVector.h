#ifndef VEAMY_VEAMYTRACTIONVECTOR_H
#define VEAMY_VEAMYTRACTIONVECTOR_H

#include <veamy/physics/traction/TractionVector.h>

/*
 * Concrete implementation of TractionVector, which computes the traction vector for linear elasticity for VEM
 */
class VeamyTractionVector : public TractionVector{
private:
    /*
     * Geometrical equivalent to the element which traction vector will be computed
     */
    Polygon p;

    /*
     * Mesh points
     */
    std::vector<Point> points;

    /*
     * Neumann or natural constraints of the system
     */
    NaturalConstraints natural;
public:
    /*
     * Constructor
     */
    VeamyTractionVector(Polygon p, UniqueList<Point> &points, NaturalConstraints &natural,
                        int n_dofs);

    /* Computes the traction load vector related to a segment of an element
     * @param segment segment which traction vector will be computed
     * @return he traction load vector related to the segment
     */
    Eigen::VectorXd computeTractionVector(IndexSegment segment);
};

#endif