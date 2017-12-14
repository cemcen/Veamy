#ifndef VEAMY_DISPDIFFERENCECOMPUTABLE_H
#define VEAMY_DISPDIFFERENCECOMPUTABLE_H

#include <veamy/postprocess/analytic/DisplacementValue.h>
#include <veamy/postprocess/computables/Computable.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/dof/DOFS.h>
#include <veamy/postprocess/calculators/DisplacementCalculator.h>

/*
 * Class that calculates the term (u-uh) dot (u-uh) of the L2 norm
 */
template <typename T>
class DisplacementDifferenceComputable : public Computable<T>{
private:
    /*
     * Analytical displacement
     */
    DisplacementValue* value;

    /*
     * Nodal displacement values
     */
    Eigen::VectorXd nodalValues;

    /*
     * Degrees of freedom of the system
     */
    DOFS dofs;

    /*
     * Instance of a displacement calculator (computes the approximated displacement uh)
     */
    DisplacementCalculator<T>* calculator;

    /*
     * Index of the polygon that contains the points in which the points are contained
     */
    int polygonIndex;
public:
    /*
     * Constructor
     */
    DisplacementDifferenceComputable(DisplacementValue *v, DisplacementCalculator<T>* calculator);

    /* Calculates the value of this particular computable on a point
     * @param x y coordinates of the point
     * @param index index of the point (if part of the mesh)
     * @param container geometric container of the point
     * @return value of the computable
     */
    double apply(double x, double y, int index, T container);

    /* Sets the index of the polygon in which the next points will be contained
    * @param polyIndex index of the polygon
    */
    void setPolygonIndex(int polyIndex);
};

#endif