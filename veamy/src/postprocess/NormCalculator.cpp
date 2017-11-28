#include <veamy/postprocess/NormCalculator.h>

template <typename T>
NormCalculator<T>::NormCalculator(Eigen::VectorXd disp, DOFS dofs) {
    this->nodalDisplacements = disp;
    this->dofs = dofs;
}

template <typename T>
double NormCalculator<T>::getNorm(Mesh<T> mesh) {
    double numerator = 0, denominator = 0;
    std::vector<T> meshElements = mesh.getPolygons();
    UniqueList<Point> points = mesh.getPoints();

    int i = 0;
    for(T elem: meshElements){
        numerator += num->getIntegral(elem, i, points.getList());
        denominator += den->getIntegral(elem, i, points.getList());
        i++;
    }

    return std::sqrt(numerator/denominator);
}

template class NormCalculator<Triangle>;
template class NormCalculator<Polygon>;