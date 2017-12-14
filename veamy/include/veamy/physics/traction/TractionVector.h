#ifndef VEAMY_TRACTIONVECTOR_H
#define VEAMY_TRACTIONVECTOR_H

#include <veamy/lib/Eigen/Dense>
#include <veamy/models/constraints/NaturalConstraints.h>

/*
 * Abstract class that models the computation of the traction part of the load vector
 */
class TractionVector{
public:
    /* Computes the traction load vector related to a segment of an element
     * @param segment segment which traction vector will be computed
     * @return he traction load vector related to the segment
     */
    virtual Eigen::VectorXd computeTractionVector(IndexSegment segment)=0;
};

#endif