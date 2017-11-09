#include <veamy/postprocess/integrator/VeamyH1Integrator.h>

template <typename T>
VeamyH1Integrator<T>::VeamyH1Integrator() {}

template <typename T>
VeamyH1Integrator<T>::VeamyH1Integrator(DisplacementValue *value, DOFS dofs, Eigen::VectorXd u) {
    this->value = value;
    this->dofs = dofs;
    this->nodalValues = u;
}

template <typename T>
double VeamyH1Integrator<T>::getIntegral(T poly, int polyIndex, std::vector<Point> points) {
    std::vector<IndexSegment> segments;
    poly.getSegments(segments);

    double result = 0;

    for(IndexSegment s: segments){
        Pair<double> u1 = value->getValue(points[s.getFirst()]);
        Pair<double> u2 = value->getValue(points[s.getSecond()]);

        Pair<int> point1_dofs = dofs.pointToDOFS(s.getFirst());
        Pair<int> point2_dofs = dofs.pointToDOFS(s.getFirst());
        Pair<double> uH1 = Pair<double>(nodalValues[point1_dofs.first], nodalValues[point1_dofs.second]);
        Pair<double> uH2 = Pair<double>(nodalValues[point2_dofs.first], nodalValues[point2_dofs.second]);

        Pair<double> e1 = u1 - uH1;
        Pair<double> e2 = u2 - uH2;

        result += (std::pow(e1.first - e2.first, 2) + std::pow(e1.second - e2.second, 2))/s.length(points);
    }

    return poly.getDiameter()*result;
}

template <typename T>
NormIntegrator<T>* VeamyH1Integrator<T>::clone() {
    return new VeamyH1Integrator<T>;
}

template <typename T>
void VeamyH1Integrator<T>::setComputable(Computable<T> *c) {
    return;
}

template class VeamyH1Integrator<Polygon>;
template class VeamyH1Integrator<Triangle>;