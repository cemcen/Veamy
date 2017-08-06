#include <veamy/models/constraints/NaturalConstraints.h>

NaturalConstraints::NaturalConstraints() {}

Eigen::VectorXd NaturalConstraints::boundaryVector(std::vector<Point> points, Polygon p, IndexSegment segment) {
    isConstrainedInfo constrainedInfo = isConstrainedBySegment(points, segment);

    if(constrainedInfo.isConstrained){
        std::vector<int> polygonPoints = p.getPoints();
        int n = (int) polygonPoints.size();

        std::vector<SegmentConstraint> constraints = segment_map[constrainedInfo.container];

        Eigen::MatrixXd Nbar;
        Nbar = Eigen::MatrixXd::Zero(2,2);
        Nbar(0,0) = 1.0/2;
        Nbar(1,1) = 1.0/2;

        Eigen::VectorXd hFirst, hSecond;
        hFirst = Eigen::VectorXd::Zero(2), hSecond = Eigen::VectorXd::Zero(2);

        for(Constraint c: constraints){
            hFirst(0) += c.getValue(points[segment.getFirst()])*c.isAffected(DOF::Axis::x);
            hFirst(1) += c.getValue(points[segment.getFirst()])*c.isAffected(DOF::Axis::y);

            hSecond(0) += c.getValue(points[segment.getSecond()])*c.isAffected(DOF::Axis::x);
            hSecond(1) += c.getValue(points[segment.getSecond()])*c.isAffected(DOF::Axis::y);
        }

        double length = segment.length(points);
        Eigen::VectorXd resultFirst = length*(Nbar.transpose()*hFirst);
        Eigen::VectorXd resultSecond = length*(Nbar.transpose()*hSecond);

        Eigen::VectorXd result(resultFirst.rows() + resultSecond.rows());
        result << resultFirst, resultSecond;

        return result;
    }

    Eigen::VectorXd zeros;
    zeros = Eigen::VectorXd::Zero(4);

    return zeros;
}

