#ifndef VEAMY_TRACTIONVECTOR_H
#define VEAMY_TRACTIONVECTOR_H

#include <veamy/lib/Eigen/Dense>
#include <veamy/models/constraints/NaturalConstraints.h>

class TractionVector{
public:
    virtual Eigen::VectorXd computeTractionVector(IndexSegment segment)=0;
};

#endif