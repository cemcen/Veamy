#include <feamy/integration/LineIntegrator.h>


Eigen::VectorXd LineIntegrator::integrate(int nGauss, PointSegment segment, IntegrableFunction *integrable) {
    Eigen::VectorXd integral;

    std::vector<double> gaussPoints, weights;
    gauss_quadrature::gauss_1d(nGauss, gaussPoints, weights);

    for (int i = 0; i < gaussPoints.size(); ++i) {
        double x = segment.getFirst().getX() +
                (segment.getSecond().getX() - segment.getFirst().getX())/2*(1+gaussPoints[i]);
        double y = segment.getFirst().getY() +
                   (segment.getSecond().getY() - segment.getFirst().getY())/2*(1+gaussPoints[i]);

        integral += weights[i]*segment.length()/2*integrable->apply(Point(x,y));
    }

    return integral;
}
