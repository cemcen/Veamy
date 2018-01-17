#ifndef VEAMY_STRAINSTRESSDIFFERENCECOMPUTABLE_H
#define VEAMY_STRAINSTRESSDIFFERENCECOMPUTABLE_H

#include <veamy/postprocess/analytic/StrainValue.h>
#include <veamy/postprocess/analytic/StressValue.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/dof/DOFS.h>
#include "H1Computable.h"
#include <feamy/problem/linear_elasticity/LinearElasticityStiffnessMatrixIntegrable.h>
#include <veamy/utilities/veamy_functions.h>
#include <feamy/models/FeamyElement.h>
#include <veamy/postprocess/calculators/StrainCalculator.h>


/*
 * Computes the term (sigma - sigmaH)*(epsilon - epsilonH) of the H1 norm.
 */
template <typename T>
class StrainStressDifferenceComputable : public H1Computable<T>{
private:
    /*
     * Analytical strain and stress values
     */
    StrainValue* strainValue;
    StressValue* stressValue;

    /*
     * Index of the polygon that contains the points that will be used next
     */
    int polygonIndex;
public:
    /*
     * Constructor
     */
    StrainStressDifferenceComputable(StrainValue *strain, StressValue *stress);

    /* Computes the value of the necessary term in a given point
     * @param p point to apply the function
     * @param t container of the point
     * @return the value of the function
     */
    double apply(double x, double y, int index, T container);

    /* Sets the index of the polygon in which the next points will be contained
     * @param polyIndex index of the polygon
     */
    void setPolygonIndex(int polyIndex);
};

#endif