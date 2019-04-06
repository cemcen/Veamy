#include <feamy/physics/FeamyTractionVector.h>
#include <veamy/physics/traction/point_forces.h>
#include <veamy/geometry/VeamyTriangle.h>
#include <feamy/integration/LineIntegrator.h>
#include <feamy/problem/linear_elasticity/LinearElasticityBoundaryVectorIntegrable.h>

FeamyTractionVector::FeamyTractionVector(Triangle t, UniqueList<Point>& points, ShapeFunctions *N, NaturalConstraints natural, int nGauss,
                                         int n_dofs, BoundaryVectorIntegrable *integrable) : TractionVector(n_dofs){
    this->t = t;
    this->points = points.getList();
    this->N = N;
    this->natural = natural;
    this->nGauss = nGauss;
    this->integrable = integrable;
}

Eigen::VectorXd FeamyTractionVector::computeTractionVector(IndexSegment segment) {
    Eigen::VectorXd result;
    result = Eigen::VectorXd::Zero(2*this->n_dofs);
    isConstrainedInfo constrainedInfo = natural.isConstrainedBySegment(points, segment);

    if (constrainedInfo.isConstrained) {
        std::vector<int> trianglePoints = t.getPoints();
        int n = (int) trianglePoints.size();

        std::vector<SegmentConstraint> constraints = natural.getConstraintInformation(constrainedInfo.container);
        VeamyTriangle triangle(t);
        int indexFirst = triangle.indexOf(segment.getFirst()), indexSecond = triangle.indexOf(segment.getSecond());
        PointSegment s(points[segment.getFirst()], points[segment.getSecond()]);
        std::vector<int> indexes = {indexFirst, indexSecond};

        for (Constraint c: constraints) {
            integrable->setConditions(c, indexes);
            LineIntegrator::integrate(result, nGauss, s, integrable);
        }
    }

    point_forces::addPointForces(result, natural, points[segment.getFirst()], points[segment.getSecond()], this->n_dofs);

    return result;
}
