#include <veamy/physics/bodyforces/VeamyBodyForceVector.h>


VeamyBodyForceVector::VeamyBodyForceVector(Polygon p, UniqueList<Point> points) {
    this->polygon = p;
    this->points = points.getList();
}

Eigen::VectorXd VeamyBodyForceVector::computeForceVector(BodyForce *f) {
    int n = this->polygon.numberOfSides();
    double integralX = veamy_functions::volume_nodal_quadrature(this->polygon, this->points, f->getX());
    double integralY = veamy_functions::volume_nodal_quadrature(this->polygon, this->points, f->getY());;

    Eigen::VectorXd result;
    result = Eigen::VectorXd::Zero(2*n);

    for (int j = 0; j < n; ++j) {
        result(2*j) = integralX;
        result(2*j+1) = integralY;
    }

    return result;
}
