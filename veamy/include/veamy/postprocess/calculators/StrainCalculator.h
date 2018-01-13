#ifndef VEAMY_STRAINCALCULATOR_H
#define VEAMY_STRAINCALCULATOR_H

#include <veamy/lib/Eigen/Dense>
#include <veamy/models/dof/DOFS.h>

/*
 * Abstract class that models the computation of the strain from the nodal results
 */
template <typename T>
class StrainCalculator {
protected:
    /*
     * Degrees of freedom of the system
     */
    DOFS d;

    /*
     * Nodal displacements
     */
    Eigen::VectorXd u;

    /*
     * Mesh points
     */
    std::vector<Point> points;
public:
    /*
     * Constructor
     */
    StrainCalculator(DOFS& d, Eigen::VectorXd u, std::vector<Point>& points){
        this->d = d;
        this->u = u;
        this->points = points;
    }

    /* Computes the approximate strain for a given point
     * @param x y coordinates of the point
     * @param container element that contains the point
     * @param containerIndex index of the container element
     * @return approximated strain
     */
    virtual Eigen::VectorXd getStrain(double x, double y, T container, int containerIndex) = 0;
};

#endif