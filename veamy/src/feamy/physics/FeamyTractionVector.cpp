#include <feamy/physics/FeamyTractionVector.h>

FeamyTractionVector::FeamyTractionVector(Triangle t, UniqueList<Point> points, ShapeFunctions *N,
                                         NaturalConstraints natural) {
    this->t;
    this->points = points.getList();
    this->N = N;
    this->natural = natural;
}

Eigen::VectorXd FeamyTractionVector::computeTractionVector(IndexSegment segment) {
    Eigen::VectorXd result(4);
    isConstrainedInfo constrainedInfo = natural.isConstrainedBySegment(points, segment);

    if (constrainedInfo.isConstrained) {
        std::vector<int> trianglePoints = t.getPoints();
        int n = (int) trianglePoints.size();

        std::vector<SegmentConstraint> constraints = natural.getConstraintInformation(constrainedInfo.container);

    } else {
        result = Eigen::VectorXd::Zero(4);
    }



}
