#include <veamy/postprocess/calculators/VeamyElasticityStrainCalculator.h>
#include <veamy/postprocess/utilities/norm_utilities.h>
#include <veamy/problems/elasticity/elasticity_functions.h>

template <typename T>
VeamyElasticityStrainCalculator<T>::VeamyElasticityStrainCalculator(DOFS &d, Eigen::VectorXd &u,
                                                                    std::vector<Point> &points) :
        StrainCalculator<T>(d, u, points) {}

template <typename T>
Eigen::VectorXd VeamyElasticityStrainCalculator<T>::getStrain(double x, double y, T container, int containerIndex) {
    Eigen::MatrixXd Wc = elasticity_functions::WcMatrix(container, this->points);
    Eigen::VectorXd d =  norm_utilities::getElementNodalValues(container, this->u, this->d);

    return Wc.transpose()*d;
}

template class VeamyElasticityStrainCalculator<Polygon>;
template class VeamyElasticityStrainCalculator<Triangle>;