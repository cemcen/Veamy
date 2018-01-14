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
        Eigen::MatrixXd J = t.getJacobian(points);

        Eigen::MatrixXd gaussPoints;
        std::vector<double> weights;
        norm_utilities::triangle_rules(gaussPoints, t, weights, nGauss, points);

        for (int i = 0; i < gaussPoints.size(); ++i) {
            Point point = Point(gaussPoints(i,0), gaussPoints(i,1));

            result += weights[i] * integrable->apply(point, t)*J.determinant()/2;
        }
    }
}

template class AreaIntegrator<VeamyTriangle,Eigen::VectorXd>;
template class AreaIntegrator<VeamyTriangle,Eigen::MatrixXd>;
template class AreaIntegrator<VeamyPolygon,Eigen::VectorXd>;
template class AreaIntegrator<VeamyPolygon,Eigen::MatrixXd>;
template class AreaIntegrator<VeamyPolygon, double>;
template class AreaIntegrator<VeamyTriangle, double>;