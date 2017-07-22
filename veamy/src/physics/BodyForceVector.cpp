#include <veamy/physics/BodyForceVector.h>
#include <veamy/lib/Eigen/Dense>

Pair<double> BodyForceVector::computeConstantForceVector(BodyForce *f, Polygon polygon, std::vector<Point> points){
    std::vector<int> polygonPoints = polygon.getPoints();
    int n = (int) polygonPoints.size();

    Eigen::MatrixXd Nbar;
    Eigen::VectorXd b;

    Nbar = Eigen::MatrixXd::Zero(2,2*n);
    b =  Eigen::VectorXd::Zero(2);

    for (int vertex_id = 0; vertex_id < n; ++vertex_id) {
        Nbar(0,2*vertex_id) = 1.0/n;
        Nbar(1,2*vertex_id + 1) = 1.0/n;
    }

    b(0) = f->applyX(0,0);
    b(1) = f->applyY(0,0);

    Eigen::VectorXd result = polygon.getArea()*Nbar.transpose()*b;

    return Pair<double>(result(0), result(1));
}

Pair<double> BodyForceVector::computeVariableForceVector(BodyForce *f, Polygon polygon, std::vector<Point> points) {
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

    return Pair<double>(integralX, integralY);
}
