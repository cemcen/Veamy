#ifndef VEAMY_LINEINTEGRATOR_H
#define VEAMY_LINEINTEGRATOR_H

#include <veamy/lib/Eigen/Dense>

class LineIntegrator {
public:
    static Eigen::VectorXd integrate(int nGauss);

};

#endif