#ifndef VEAMY_VEAMYSTRAINCALCULATOR_H
#define VEAMY_VEAMYSTRAINCALCULATOR_H

#include "StrainCalculator.h"

template <typename T>
class VeamyStrainCalculator : public StrainCalculator<T>{
public:
    /*
     * Constructor
     */
    VeamyStrainCalculator(DOFS& d, Eigen::VectorXd u, std::vector<Point>& points);

    /* Computes the approximate strain for a given point
     * @param x y coordinates of the point
     * @param container element that contains the point
     * @param containerIndex index of the container element
     * @return approximated strain
     */
    Eigen::VectorXd getStrain(double x, double y, T container, int containerIndex);
};

#endif