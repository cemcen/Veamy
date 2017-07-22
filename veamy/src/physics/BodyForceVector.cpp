#include <veamy/physics/BodyForceVector.h>
#include <veamy/lib/Eigen/Dense>


BodyForceVector::BodyForceVector(Polygon p) {
    this->polygon = p;
}

double BodyForceVector::computeVector(BodyForce *f, std::vector<Point> points) {
    std::vector<int> polygonPoints = polygon.getPoints();
    int n = (int) polygonPoints.size();

    Eigen::MatrixXd Nbar;
    Nbar = Eigen::MatrixXd::Zero(2,2*n);

    for (int vertex_id = 0; vertex_id < n; ++vertex_id) {
        Nbar(0,2*vertex_id) = 1.0/n;
        Nbar(1,2*vertex_id + 1) = 1.0/n;

    }

    return 0;
}

