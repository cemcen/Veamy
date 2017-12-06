#ifndef VEAMY_VEAMYTRACTIONVECTOR_H
#define VEAMY_VEAMYTRACTIONVECTOR_H

#include <veamy/physics/traction/TractionVector.h>

class VeamyTractionVector : public TractionVector{
private:
    Polygon p;
    std::vector<Point> points;
    NaturalConstraints natural;
public:
    VeamyTractionVector(Polygon p, UniqueList<Point> points, NaturalConstraints natural);
    Eigen::VectorXd computeTractionVector(IndexSegment segment);
};

#endif