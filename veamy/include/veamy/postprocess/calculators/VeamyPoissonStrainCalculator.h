#ifndef VEAMY_VEAMYPOISSONSTRAINCALCULATOR_H
#define VEAMY_VEAMYPOISSONSTRAINCALCULATOR_H

#include "StrainCalculator.h"
#include <veamy/problems/poisson/poisson_functions.h>
#include <veamy/postprocess/utilities/norm_utilities.h>

template <typename T>
class VeamyPoissonStrainCalculator : public StrainCalculator<T>{
public:
    /*
     * Constructor
     */
    VeamyPoissonStrainCalculator(DOFS& d, Eigen::VectorXd u, std::vector<Point>& points);

    /* Computes the approximate strain for a given point
     * @param x y coordinates of the point
     * @param container element that contains the point
     * @param containerIndex index of the container element
     * @return approximated strain
     */
    Eigen::VectorXd getStrain(double x, double y, T container, int containerIndex);

};

#endif