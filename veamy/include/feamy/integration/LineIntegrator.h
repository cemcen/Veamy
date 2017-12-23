#ifndef VEAMY_LINEINTEGRATOR_H
#define VEAMY_LINEINTEGRATOR_H

#include <veamy/lib/Eigen/Dense>
#include <feamy/integration/integrables/IntegrableFunction.h>
#include <delynoi/models/basic/PointSegment.h>
#include <feamy/integration/quadrature/gauss_quadrature.h>

/*
 * Class that integrates a given function (represented by an IntegrableFunction) on a line
 */
class LineIntegrator {
public:
    /*
     * Computes the integral on a line
     * @param s vector where the result of the integration will be set
     * @param nGauss number of gauss integration points that will be used
     * @param segment line where the integral will be computed
     * @param integrable function to integrate
     */
    static void integrate(Eigen::VectorXd& S, int nGauss, PointSegment segment, IntegrableFunction<Eigen::VectorXd>* integrable);
};

#endif