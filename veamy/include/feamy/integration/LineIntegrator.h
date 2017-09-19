#ifndef VEAMY_LINEINTEGRATOR_H
#define VEAMY_LINEINTEGRATOR_H

#include <veamy/lib/Eigen/Dense>
#include <feamy/integration/integrables/IntegrableFunction.h>
#include <delynoi/models/basic/PointSegment.h>
#include <feamy/integration/quadrature/gauss_quadrature.h>

class LineIntegrator {
public:
    static void integrate(Eigen::VectorXd& S, int nGauss, PointSegment segment, IntegrableFunction<Eigen::VectorXd>* integrable);
};

#endif