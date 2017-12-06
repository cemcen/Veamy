#ifndef VEAMY_DISPLACEMENTCALCULATOR_H
#define VEAMY_DISPLACEMENTCALCULATOR_H

#include <utilities/Pair.h>
#include <veamy/models/dof/DOFS.h>
#include <veamy/lib/Eigen/Dense>

template <typename T>
class DisplacementCalculator {
protected:
    DOFS dofs;
    Eigen::VectorXd nodalValues;
public:
    DisplacementCalculator(DOFS d, Eigen::VectorXd u);
    virtual Pair<double> getDisplacement(double x, double y, int index, T container) = 0;
    virtual void setPolygonIndex(int polyIndex){}
};

#endif