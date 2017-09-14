#ifndef VEAMY_FEAMYTRACTIONVECTOR_H
#define VEAMY_FEAMYTRACTIONVECTOR_H

#include <veamy/physics/traction/TractionVector.h>
#include <delynoi/models/polygon/Triangle.h>
#include <feamy/models/shapefunctions/ShapeFunctions.h>

class FeamyTractionVector : public TractionVector{
private:
    Triangle t;
    std::vector<Point> points;
    NaturalConstraints natural;
    ShapeFunctions* N;
    int nGauss;
public:
    FeamyTractionVector(Triangle t, UniqueList<Point> points, ShapeFunctions* N, NaturalConstraints natural, int nGauss);
    Eigen::VectorXd computeTractionVector(IndexSegment segment);
};

#endif