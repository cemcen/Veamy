#include <feamy/physics/FeamyTractionVector.h>

FeamyTractionVector::FeamyTractionVector(Triangle t, UniqueList<Point> points, ShapeFunctions *N,
                                         NaturalConstraints natural) {
    this->t;
    this->points = points.getList();
    this->N = N;
    this->natural = natural;
}

Eigen::VectorXd FeamyTractionVector::computeTractionVector(IndexSegment segment) {
    return Eigen::VectorXd();
}
