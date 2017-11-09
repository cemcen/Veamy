#include <feamy/integration/AreaIntegrator.h>
#include <feamy/integration/quadrature/gauss_quadrature.h>
#include <delynoi/models/polygon/Triangle.h>
#include <veamy/geometry/VeamyTriangle.h>
#include <veamy/geometry/VeamyPolygon.h>

template <typename T, typename S>
void AreaIntegrator<T,S>::integrate(S& result, int nGauss, T element, std::vector<Point> points,
                                          IntegrableFunction<S> *integrable) {
    std::vector<VeamyTriangle> triangles = element.triangulate(points);

    for(VeamyTriangle t: triangles){
        std::vector<Point> p = t.getPoints(points);
        Eigen::MatrixXd J = t.getJacobian(points);

        std::vector<Point> gaussPoints;
        std::vector<double> weights;
        gauss_quadrature::gauss_triangle(nGauss, gaussPoints, weights);

        for (int i = 0; i < gaussPoints.size(); ++i) {
            double g1 = p[0].getX() + (p[1].getX() - p[0].getX())*gaussPoints[i].getX()  +
                    (p[2].getX() - p[0].getX())*gaussPoints[i].getY();
            double g2 = p[0].getY() + (p[1].getY() - p[0].getY())*gaussPoints[i].getX()  +
                        (p[2].getY() - p[0].getY())*gaussPoints[i].getY();

            result += weights[i] * integrable->apply(Point(g1, g2), t);
        }
    }
}

template class AreaIntegrator<VeamyTriangle,Eigen::VectorXd>;
template class AreaIntegrator<VeamyTriangle,Eigen::MatrixXd>;
template class AreaIntegrator<VeamyPolygon,Eigen::VectorXd>;
template class AreaIntegrator<VeamyPolygon,Eigen::MatrixXd>;
template class AreaIntegrator<VeamyPolygon, double>;
template class AreaIntegrator<VeamyTriangle, double>;