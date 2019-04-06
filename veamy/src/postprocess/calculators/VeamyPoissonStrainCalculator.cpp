#include <veamy/postprocess/calculators/VeamyPoissonStrainCalculator.h>

template <typename T>
VeamyPoissonStrainCalculator<T>::VeamyPoissonStrainCalculator(DOFS &d, Eigen::VectorXd& u, std::vector<Point> &points)
        : StrainCalculator<T>(d, u, points) {}

template <typename T>
Eigen::VectorXd VeamyPoissonStrainCalculator<T>::getStrain(double x, double y, T container, int containerIndex) {
    Eigen::MatrixXd W = poisson_functions::WMatrix(container, this->points);
    Eigen::VectorXd d =  norm_utilities::getElementNodalValues(container, this->u, this->d);

    return W.transpose()*d;
}

template class VeamyPoissonStrainCalculator<Polygon>;
template class VeamyPoissonStrainCalculator<Triangle>;
