#ifndef VEAMY_VEAMYPOISSONDISPLACEMENTCALCULATOR_H
#define VEAMY_VEAMYPOISSONDISPLACEMENTCALCULATOR_H

#include <delynoi/models/polygon/Polygon.h>
#include "DisplacementCalculator.h"

/*
 * Class that models the computation of the approximated displacement for norm computation for VEM solving the Poisson
 * problem
 */
template <typename T>
class VeamyPoissonDisplacementCalculator : public DisplacementCalculator<T>{
private:
    /*
     * Mesh points
     */
    std::vector<Point> points;
public:
    /*
     * Constructor
     */
    VeamyPoissonDisplacementCalculator(DOFS d, Eigen::VectorXd u, std::vector<Point>& points);

    /* Computes the approximate displacement for a given point
     * @param x y coordinates of the point
     * @param index index of the point (if part of the mesh)
     * @param container element that contains the point
     * @return approximated displacement
     */
    std::vector<double> getDisplacement(double x, double y, int index, T container);
};

#endif