#include <veamy/postprocess/NormCalculator.h>
#include <veamy/postprocess/utilities/NormResult.h>

template <typename T>
NormCalculator<T>::NormCalculator(Eigen::VectorXd disp, DOFS dofs) {
    this->nodalDisplacements = disp;
    this->dofs = dofs;
}

template <typename T>
NormResult NormCalculator<T>::getNorm(Mesh<T> &mesh) {
    double numerator = 0, denominator = 0;
    std::vector<T> meshElements = mesh.getPolygons();
    UniqueList<Point> points = mesh.getPoints();
    std::vector<double> maxEdge;

    int i = 0;
    for(T elem: meshElements){
        numerator += num->getIntegral(elem, i, points.getList());
        denominator += den->getIntegral(elem, i, points.getList());

        maxEdge.push_back(elem.getMaxDistance(points.getList()));
        i++;
    }

    return NormResult(std::sqrt(numerator/denominator), *std::min_element(maxEdge.begin(), maxEdge.end()));
}

template class NormCalculator<Triangle>;
template class NormCalculator<Polygon>;
