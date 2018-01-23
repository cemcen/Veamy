#include <feamy/integration/AreaIntegrator.h>
#include <feamy/integration/quadrature/gauss_quadrature.h>
#include <delynoi/models/polygon/Triangle.h>
#include <veamy/geometry/VeamyTriangle.h>
#include <veamy/geometry/VeamyPolygon.h>
#include <veamy/postprocess/utilities/norm_utilities.h>

template <typename T, typename S>
void AreaIntegrator<T,S>::integrate(S& result, int nGauss, T element, std::vector<Point> points,
                                          IntegrableFunction<S> *integrable) {
    std::vector<VeamyTriangle> triangles = element.triangulate(points);

    for(VeamyTriangle t: triangles){
        std::vector<Point> p = t.getPoints(points);

        Eigen::MatrixXd gaussPoints;
        std::vector<double> weights;
        gauss_quadrature::triangle_rules(gaussPoints, t, weights, nGauss, points);

        for (int i = 0; i < weights.size(); ++i) {
            Point point = Point(gaussPoints(i,0), gaussPoints(i,1));
            result += weights[i] * integrable->apply(point, t);            
        }
    }
}

template class AreaIntegrator<VeamyTriangle,Eigen::VectorXd>;
template class AreaIntegrator<VeamyTriangle,Eigen::MatrixXd>;
template class AreaIntegrator<VeamyPolygon,Eigen::VectorXd>;
template class AreaIntegrator<VeamyPolygon,Eigen::MatrixXd>;
template class AreaIntegrator<VeamyPolygon, double>;
template class AreaIntegrator<VeamyTriangle, double>;