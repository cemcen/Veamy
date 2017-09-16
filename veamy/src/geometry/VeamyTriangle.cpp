#include <veamy/geometry/VeamyTriangle.h>

VeamyTriangle::VeamyTriangle() {
    this->points.push_back(-1);
}

VeamyTriangle::VeamyTriangle(Triangle t) : Triangle(t){}

VeamyTriangle::VeamyTriangle(int p1, int p2, int p3) {
    this->points.push_back(p1);
    this->points.push_back(p1);
    this->points.push_back(p1);
}

std::vector<VeamyTriangle> VeamyTriangle::triangulate(std::vector<Point> points) {
    std::vector<VeamyTriangle> triangles = {*this};
    return triangles;
}

Eigen::MatrixXd VeamyTriangle::getJacobian(std::vector<Point> p) {
    Eigen::MatrixXd J;
    J = Eigen::MatrixXd::Zero(2,2);

    J(0,0) = p[points[0]].getX() - p[points[2]].getX();
    J(0,1) = p[points[0]].getY() - p[points[2]].getY();
    J(1,0) = p[points[1]].getX() - p[points[2]].getX();
    J(1,1) = p[points[1]].getY() - p[points[2]].getY();

    return J;
}

bool VeamyTriangle::isNull() {
    return this->points[0]<0;
}

int VeamyTriangle::indexOf(int i) {
    return utilities::indexOf(this->points, i);
}
