#include <veamy/physics/traction/VeamyTractionVector.h>
#include <veamy/physics/traction/point_forces.h>

VeamyTractionVector::VeamyTractionVector(Polygon p, UniqueList<Point> points, NaturalConstraints natural,
                                         int n_dofs) : TractionVector(n_dofs){
    this->p = p;
    this->points = points.getList();
    this->natural = natural;
}

Eigen::VectorXd VeamyTractionVector::computeTractionVector(IndexSegment segment) {
    Eigen::VectorXd result(2*this->n_dofs);
    isConstrainedInfo constrainedInfo = natural.isConstrainedBySegment(points, segment);

    if(constrainedInfo.isConstrained){
        std::vector<int> polygonPoints = p.getPoints();
        int n = (int) polygonPoints.size();

        std::vector<SegmentConstraint> constraints = natural.getConstraintInformation(constrainedInfo.container);

        Eigen::MatrixXd Nbar;
        Nbar = Eigen::MatrixXd::Zero(this->n_dofs,this->n_dofs);

        for (int j = 0; j < this->n_dofs; ++j) {
            Nbar(j,j) = 1.0/2;
        }

        Eigen::VectorXd hFirst, hSecond;
        hFirst = Eigen::VectorXd::Zero(this->n_dofs), hSecond = Eigen::VectorXd::Zero(this->n_dofs);

        for(Constraint c: constraints){
            for (int i = 0; i < this->n_dofs; ++i) {
                hFirst(i) += c.getValue(points[segment.getFirst()])*c.isAffected(i);
            }

            for (int i = 0; i < this->n_dofs; ++i) {
                hSecond(i) += c.getValue(points[segment.getSecond()])*c.isAffected(i);
            }
        }

        double length = segment.length(points);
        Eigen::VectorXd resultFirst = length*(Nbar.transpose()*hFirst);
        Eigen::VectorXd resultSecond = length*(Nbar.transpose()*hSecond);

        result << resultFirst, resultSecond;
    } else {
        result = Eigen::VectorXd::Zero(2*this->n_dofs);
    }

    point_forces::addPointForces(result, natural, points[segment.getFirst()], points[segment.getSecond()], this->n_dofs);

    return result;
}
