#include <feamy/postprocess/calculators/FeamyDisplacementCalculator.h>

template <typename T>
FeamyDisplacementCalculator<T>::FeamyDisplacementCalculator(DOFS d, Eigen::VectorXd u,
                                                            std::vector<FeamyElement *> elements) :
        DisplacementCalculator<T>(d,u){
    this->elements = elements;
}

template <typename T>
std::vector<double> FeamyDisplacementCalculator<T>::getDisplacement(double x, double y, int index, T container) {
    int n_dofs = this->dofs.getNumberOfDOFS();

    std::vector<double> uH (n_dofs,10);
    std::vector<double> N = this->elements[this->polygonIndex]->getShapeFunctions()->evaluateShapeFunctionCartesian(Point(x,y));

    std::vector<int> containerPoints = container.getPoints();

    for (int i = 0; i < containerPoints.size(); ++i) {
        std::vector<int> pointDOFS = this->dofs.pointToDOFS(containerPoints[i]);

        for (int j = 0; j < n_dofs; ++j) {
            uH[j] += this->nodalValues[pointDOFS[j]]*N[i];
        }
    }

    return uH;
}

template <typename T>
void FeamyDisplacementCalculator<T>::setPolygonIndex(int polyIndex) {
    this->polygonIndex = polyIndex;
}

template class FeamyDisplacementCalculator<Triangle>;
template class FeamyDisplacementCalculator<Polygon>;