#include <veamy/physics/bodyforces/VeamyBodyForceVector.h>


VeamyBodyForceVector::VeamyBodyForceVector(Polygon p, UniqueList<Point> points) {
    this->polygon = p;
    this->points = points.getList();
}

Eigen::VectorXd VeamyBodyForceVector::computeForceVector(BodyForce *f) {
    int n = this->polygon.numberOfSides();

    int dofs = f->numberOfComponents();
    std::vector<double> integrals;
    std::vector<FunctionComputable*> components = f->getComponents();

    for (int i = 0; i < dofs; ++i) {
        integrals.push_back(veamy_functions::nodal_quadrature(this->polygon, this->points, components[i]));
    }

    Eigen::VectorXd result;
    result = Eigen::VectorXd::Zero(n*dofs);

    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < dofs; ++i) {
            result(j*dofs + i) = integrals[i];
        }
    }

    return result;
}
