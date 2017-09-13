#include <veamy/physics/bodyforces/VeamyBodyForceVector.h>

VeamyBodyForceVector::VeamyBodyForceVector(Polygon p, UniqueList<Point> points) {
    this->polygon = p;
    this->points = points.getList();
}

Eigen::VectorXd VeamyBodyForceVector::computeForceVector(BodyForce *f) {
    double integralX = 0;
    double integralY = 0;

    std::vector<int> polygonPoints = polygon.getPoints();
    int n = (int) polygonPoints.size();

    IndexSegment prev;
    IndexSegment next;

    for (int i = 0; i < n; ++i) {
        prev = IndexSegment(polygonPoints[(n+i-1)%n], polygonPoints[i]);
        next = IndexSegment(polygonPoints[i], polygonPoints[(i+1)%n]);

        Point point = points[polygonPoints[i]];
        std::vector<Point> smallPolygon = {prev.middlePoint(points), points[polygonPoints[i]],
                                           next.middlePoint(points), polygon.getCentroid()};

        double area = geometry_functions::area(smallPolygon);

        integralX += area*f->applyX(point.getX(), point.getY());
        integralY += area*f->applyX(point.getX(), point.getY());
    }

    Eigen::VectorXd result;
    result = Eigen::VectorXd::Zero(2*n);

    for (int j = 0; j < n; ++j) {
        result(2*j) = integralX;
        result(2*j+1) = integralY;
    }

    return result;
}
