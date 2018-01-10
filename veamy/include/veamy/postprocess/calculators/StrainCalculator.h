#ifndef VEAMY_STRAINCALCULATOR_H
#define VEAMY_STRAINCALCULATOR_H

#include <veamy/lib/Eigen/Dense>
#include <veamy/models/dof/DOFS.h>

/*
 *
 */
template <typename T>
class StrainCalculator {
protected:
    DOFS d;
    Eigen::VectorXd u;
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

    /*
     *
     */
    virtual Eigen::VectorXd getStrain(double x, double y, T container, int containerIndex) = 0;
};

#endif