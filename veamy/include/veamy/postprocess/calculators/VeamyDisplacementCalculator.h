#ifndef VEAMY_VEAMYDISPLACEMENTCALCULATOR_H
#define VEAMY_VEAMYDISPLACEMENTCALCULATOR_H

#include <utilities/Pair.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/dof/DOFS.h>
#include "DisplacementCalculator.h"

template <typename T>
class VeamyDisplacementCalculator : public DisplacementCalculator<T>{
public:
    VeamyDisplacementCalculator(DOFS d, Eigen::VectorXd u);
    Pair<double> getDisplacement(double x, double y, int index, T container);
};

#endif