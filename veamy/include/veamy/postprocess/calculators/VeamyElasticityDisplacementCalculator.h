#ifndef VEAMY_VEAMYDISPLACEMENTCALCULATOR_H
#define VEAMY_VEAMYDISPLACEMENTCALCULATOR_H

#include <utilities/Pair.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/dof/DOFS.h>
#include "DisplacementCalculator.h"

/*
 * Class that models the computation of the approximated displacement for norm computation for VEM. It is important to note
 * that, as VEM does not use shape functions, the norms use the nodal values directly, so this class is simple
 */
template <typename T>
class VeamyElasticityDisplacementCalculator : public DisplacementCalculator<T>{
private:
    /*
     * Mesh points
     */
    std::vector<Point> points;
public:
    /*
     * Constructor
     */
    VeamyElasticityDisplacementCalculator(DOFS d, Eigen::VectorXd u, std::vector<Point>& points);

    /* Computes the approximate displacement for a given point
     * @param x y coordinates of the point
     * @param index index of the point (if part of the mesh)
     * @param container element that contains the point
     * @return approximated displacement
     */
    std::vector<double> getDisplacement(double x, double y, int index, T container);
};

#endif