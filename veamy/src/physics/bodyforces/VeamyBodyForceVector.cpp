#include <veamy/physics/bodyforces/VeamyBodyForceVector.h>


VeamyBodyForceVector::VeamyBodyForceVector(Polygon p, UniqueList<Point>& points) {
    this->polygon = p;
    this->points = points.getList();
}

Eigen::VectorXd VeamyBodyForceVector::computeForceVector(BodyForce *f) {
    int n = this->polygon.numberOfSides();
    std::vector<int> polygonPoints = this->polygon.getPoints();
    double area = this->polygon.getArea(this->points);

    int dofs = f->numberOfComponents();
    std::vector<FunctionComputable*> components = f->getComponents();

    Eigen::VectorXd result;
    result = Eigen::VectorXd::Zero(n*dofs);

    for (int i = 0; i < n; ++i) {
        Point point = points[polygonPoints[i]];

         for (int j = 0; j < dofs; ++j){
            double res = components[j]->apply(point.getX(), point.getY(), polygonPoints[i], this->polygon);

            result(i*dofs + j) = area*res/n;
        }
    }

    return result;
}
