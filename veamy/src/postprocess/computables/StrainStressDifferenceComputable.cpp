#include <veamy/postprocess/computables/StrainStressDifferenceComputable.h>

template <typename T>
StrainStressDifferenceComputable<T>::StrainStressDifferenceComputable(StrainValue *strain, StressValue *stress,
                                                                   Eigen::VectorXd u, DOFS d, std::vector<FeamyElement*> elements,
                                                                   std::vector<Point> p, Eigen::MatrixXd C) {
    this->strainValue = strain;
    this->stressValue = stress;
    this->nodalValues = u;
    this->dofs = d;
    this->elements = elements;
    this->points = p;
    this->C = C;
}

template <typename T>
double StrainStressDifferenceComputable<T>::apply(double x, double y, int index, T container) {
    Eigen::VectorXd uH;
    uH = Eigen::VectorXd::Zero(2*container.numberOfSides());

    std::vector<int> containerPoints = container.getPoints();
    for (int i = 0; i < container.numberOfSides(); ++i) {
        std::vector<int> point_dofs = dofs.pointToDOFS(containerPoints[i]);

        uH(2*i) = nodalValues[point_dofs[0]];
        uH(2*i + 1) = nodalValues[point_dofs[1]];

    }

    Eigen::MatrixXd Be = LinearElasticityStiffnessMatrixIntegrable().BeMatrix(Point(x,y), VeamyTriangle(container).getJacobian(this->points),
                                                           this->elements[this->polygonIndex]->getShapeFunctions());

    Eigen::VectorXd strain = Be*uH;
    Eigen::VectorXd stress = this->C*strain;

    Trio<double> eH = veamy_functions::to_trio<double>(strain);
    Trio<double> sH = veamy_functions::to_trio<double>(stress);
    Trio<double> e = this->strainValue->getValue(Point(x,y));
    Trio<double> s = this->stressValue->getValue(Point(x,y));

    return (e - eH).dot(s - sH);
}

template <typename T>
void StrainStressDifferenceComputable<T>::setPolygonIndex(int polyIndex) {
    this->polygonIndex = polyIndex;
}

template class StrainStressDifferenceComputable<Polygon>;
template class StrainStressDifferenceComputable<Triangle>;