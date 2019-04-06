#ifndef VEAMY_DISPLACEMENTCALCULATOR_H
#define VEAMY_DISPLACEMENTCALCULATOR_H

#include <utilities/Pair.h>
#include <veamy/models/dof/DOFS.h>
#include <veamy/lib/Eigen/Dense>

/*
 * Abstract class that models the computation of the displacement from the nodal results
 */
template <typename T>
class DisplacementCalculator{
protected:
    /*
     * Degrees of freedom of the system
     */
    DOFS dofs;

    /*
     * Nodal displacement results
     */
    Eigen::VectorXd nodalValues;
public:
    /*
     * Constructor
     */
    DisplacementCalculator(DOFS &d, Eigen::VectorXd &u);

    /* Computes the approximate displacement for a given point
     * @param x y coordinates of the point
     * @param index index of the point (if part of the mesh)
     * @param container element that contains the point
     * @return approximated displacement
     */
    virtual std::vector<double> getDisplacement(double x, double y, int index, T container) = 0;

    /* Sets the index of the polygon in which the next points will be contained
     * @param polyIndex index of the polygon
     */
    virtual void setPolygonIndex(int polyIndex){}
};

#endif