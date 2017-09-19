#include <feamy/integration/LineIntegrator.h>

void LineIntegrator::integrate(Eigen::VectorXd& result, int nGauss, PointSegment segment, IntegrableFunction<Eigen::VectorXd> *integrable) {
    std::vector<double> gaussPoints, weights;
    gauss_quadrature::gauss_1d(nGauss, gaussPoints, weights);

    for (int i = 0; i < gaussPoints.size(); ++i) {
        double x = (segment.getFirst().getX() + segment.getSecond().getX())/2 +
                (segment.getSecond().getX() - segment.getFirst().getX())/2*gaussPoints[i];
        double y = (segment.getFirst().getY() + segment.getSecond().getY())/2 +
                   (segment.getSecond().getY() - segment.getFirst().getY())/2*gaussPoints[i];

        result += weights[i]*segment.length()/2*integrable->apply(Point(x,y));
    }
}
