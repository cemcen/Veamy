#include <veamy/postprocess/calculators/VeamyStrainCalculator.h>
#include <veamy/postprocess/utilities/norm_utilities.h>

template <typename T>
VeamyStrainCalculator<T>::VeamyStrainCalculator(DOFS &d, Eigen::VectorXd u, std::vector<Point> &points) :
        StrainCalculator<T>(d, u, points) {}

template <typename T>
Eigen::VectorXd VeamyStrainCalculator<T>::getStrain(double x, double y, T container, int containerIndex) {
    Eigen::MatrixXd Wc = norm_utilities::WcMatrix(container, this->points);
    Eigen::VectorXd d =  norm_utilities::getElementNodalValues(container, this->u, this->d);

    return Wc.transpose()*d;
}
