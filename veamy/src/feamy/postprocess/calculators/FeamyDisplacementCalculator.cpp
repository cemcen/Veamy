#include <feamy/postprocess/calculators/FeamyDisplacementCalculator.h>

template <typename T>
FeamyDisplacementCalculator<T>::FeamyDisplacementCalculator(DOFS d, Eigen::VectorXd u, std::vector<FeamyElement*> elements) :
        DisplacementCalculator<T>(d,u){
    this->elements = elements;
}

template <typename T>
Pair<double> FeamyDisplacementCalculator<T>::getDisplacement(double x, double y, int index, T container) {
    double uHx = 0, uHy = 0;
    std::vector<double> N = this->elements[this->polygonIndex]->getShapeFunctions()->evaluateShapeFunctionCartesian(Point(x,y));

    std::vector<int> containerPoints = container.getPoints();

    for (int i = 0; i < containerPoints.size(); ++i) {
        Pair<int> pointDOFS = this->dofs.pointToDOFS(containerPoints[i]);

        uHx += this->nodalValues[pointDOFS.first]*N[i];
        uHy += this->nodalValues[pointDOFS.second]*N[i];
    }

    return Pair<double>(uHx, uHy);
}

template <typename T>
void FeamyDisplacementCalculator<T>::setPolygonIndex(int polyIndex) {
    this->polygonIndex = polyIndex;
}

template class FeamyDisplacementCalculator<Triangle>;
template class FeamyDisplacementCalculator<Polygon>;