#ifndef VEAMY_AREAINTEGRATOR_H
#define VEAMY_AREAINTEGRATOR_H

#include <veamy/lib/Eigen/Dense>
#include <feamy/integration/IntegrableFunction.h>
#include <delynoi/models/basic/Point.h>

/*
 * Class that integrates a given function (represented by an IntegrableFunction) on a surface
 */
template <typename T, typename S>
class AreaIntegrator {
public:
    /*
     * Computes the integral on a surface
     * @param s vector where the result of the integration will be set
     * @param nGauss number of gauss integration points that will be used
     * @param element element (surface) where the integral is to be computed
     * @param points mesh points (that element reference)
     * @param integrable function to integrate
     */
    static void integrate(S& result, int nGauss, T element, std::vector<Point> points, IntegrableFunction<S>* integrable);
};

#endif