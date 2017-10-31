#include <veamy/postprocess/NormCalculator.h>
#include <veamy/lib/Eigen/src/Core/Matrix.h>

template <typename T>
NormCalculator::NormCalculator(Eigen::VectorXd disp, DOFS dofs) {
    this->nodalDisplacements = disp;
    this->dofs = dofs;
}

template <typename T>
double NormCalculator::getNorm(Mesh<T> mesh) {
    double numerator = 0, denominator = 0;
    std::vector<T> meshElements = mesh.getPolygons();
    UniqueList<Point> points = mesh.getPoints();

    for(T elem: meshElements){
        numerator += num->getIntegral(elem, points.getList());
        denominator += den->getIntegral(elem, points.getList());
    }

    return std::sqrt(numerator/denominator);
}

template <typename T>
void NormCalculator<T>::setCalculators(NormIntegrator *num, NormIntegrator *den) {
    this->num = num;
    this->den = den;
}
