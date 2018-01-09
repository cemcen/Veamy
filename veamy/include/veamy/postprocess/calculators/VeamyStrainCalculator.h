#ifndef VEAMY_VEAMYSTRAINCALCULATOR_H
#define VEAMY_VEAMYSTRAINCALCULATOR_H

#include "StrainCalculator.h"

template <typename T>
class VeamyStrainCalculator : public StrainCalculator<T>{
public:
    VeamyStrainCalculator(DOFS& d, Eigen::VectorXd u, std::vector<Point>& points);
    Eigen::VectorXd getStrain(double x, double y, T container, int containerIndex);
};

#endif