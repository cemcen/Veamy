#ifndef VEAMY_AREAINTEGRATOR_H
#define VEAMY_AREAINTEGRATOR_H

#include <veamy/lib/Eigen/Dense>
#include <feamy/integration/integrables/IntegrableFunction.h>
#include <delynoi/models/basic/Point.h>

template <typename T, typename S>
class AreaIntegrator {
public:
    static void integrate(S& result, int nGauss, T element, std::vector<Point> points, IntegrableFunction<S>* integrable);
};

#endif