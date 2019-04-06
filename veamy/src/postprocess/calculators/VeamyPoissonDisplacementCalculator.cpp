#include <veamy/postprocess/calculators/VeamyPoissonDisplacementCalculator.h>
#include <veamy/problems/poisson/poisson_functions.h>
#include <veamy/postprocess/utilities/norm_utilities.h>

template <typename T>
VeamyPoissonDisplacementCalculator<T>::VeamyPoissonDisplacementCalculator(DOFS &d, Eigen::VectorXd &u,
                                                                          std::vector<Point> &points) :
        DisplacementCalculator<T>(d, u) {
    this->points = points;
}

template <typename T>
std::vector<double> VeamyPoissonDisplacementCalculator<T>::getDisplacement(double x, double y, int index, T container) {
    Point average = container.getAverage(this->points);

    Eigen::VectorXd X, Xbar;
    X = Eigen::VectorXd::Zero(2), Xbar = Eigen::VectorXd::Zero(2);

    X(0) = x; X(1) = y;
    Xbar(0) = average.getX(); Xbar(1) = average.getY();

    Eigen::MatrixXd W = poisson_functions::WMatrix(container, this->points);
    Eigen::VectorXd d =  norm_utilities::getElementNodalValues(container, this->nodalValues, this->dofs);

    Eigen::VectorXd uhProyection = d.transpose()*W*(X-Xbar) +  norm_utilities::getAverage(d, 1);

    std::vector<double> uH = {uhProyection(0)};
    return uH;
}

template class VeamyPoissonDisplacementCalculator<Triangle>;
template class VeamyPoissonDisplacementCalculator<Polygon>;