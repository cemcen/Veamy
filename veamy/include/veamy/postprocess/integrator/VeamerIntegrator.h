#ifndef VEAMY_VEAMERCALCULATOR_H
#define VEAMY_VEAMERCALCULATOR_H

#include <veamy/utilities/Computable.h>
#include "NormIntegrator.h"

template <typename T>
class VeamerIntegrator : public NormIntegrator {
private:
    Computable* computable;
public:
    VeamerIntegrator();
    VeamerIntegrator(Computable* computable);
    double getIntegral(T poly, std::vector<Point> points);
    void setComputable(Computable* c);
};

#endif