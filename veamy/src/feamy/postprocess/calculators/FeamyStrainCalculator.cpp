#include <feamy/postprocess/calculators/FeamyStrainCalculator.h>
#include <feamy/problem/linear_elasticity/LinearElasticityStiffnessMatrixIntegrable.h>
#include <veamy/postprocess/utilities/norm_utilities.h>

template <typename T>
FeamyStrainCalculator<T>::FeamyStrainCalculator(std::vector<Point> &points, std::vector<FeamyElement *>& elements,
                                             Eigen::VectorXd& u, DOFS &d) : StrainCalculator<T>(d, u, points) {
    this->elements = elements;
}

template <typename T>
Eigen::VectorXd FeamyStrainCalculator<T>::getStrain(double x, double y, T container, int containerIndex) {
    Eigen::VectorXd uH = norm_utilities::getElementNodalValues(container, this->u, this->d);

    Eigen::MatrixXd Be = LinearElasticityStiffnessMatrixIntegrable().BeMatrix(Point(x,y),
                                                                              VeamyTriangle(container).getJacobian(this->points),
                                                                              this->elements[containerIndex]->getShapeFunctions());

    Eigen::VectorXd strain = Be*uH;

    return strain;
}

template class FeamyStrainCalculator<Polygon>;
template class FeamyStrainCalculator<Triangle>;