#include <feamy/physics/FeamyTractionVector.h>
#include <veamy/physics/traction/point_forces.h>
#include <veamy/geometry/VeamyTriangle.h>
#include <feamy/integration/LineIntegrator.h>
#include <feamy/integration/integrables/BoundaryVectorIntegrable.h>

FeamyTractionVector::FeamyTractionVector(Triangle t, UniqueList<Point> points, ShapeFunctions *N,
                                         NaturalConstraints natural, int nGauss) {
    this->t;
    this->points = points.getList();
    this->N = N;
    this->natural = natural;
    this->nGauss = nGauss;
}

Eigen::VectorXd FeamyTractionVector::computeTractionVector(IndexSegment segment) {
    Eigen::VectorXd result(4);
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
            BoundaryVectorIntegrable* integrable = new BoundaryVectorIntegrable(c, this->N, indexes);
            result += LineIntegrator::integrate(nGauss, s, integrable);
            delete integrable;
        }
    } else {
        result = Eigen::VectorXd::Zero(4);
    }

    point_forces::addPointForces(result, natural, points[segment.getFirst()], points[segment.getSecond()]);

    return result;
}
