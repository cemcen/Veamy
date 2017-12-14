#ifndef VEAMY_STRAINSTRESSDIFFERENCECOMPUTABLE_H
#define VEAMY_STRAINSTRESSDIFFERENCECOMPUTABLE_H

#include <veamy/postprocess/analytic/StrainValue.h>
#include <veamy/postprocess/analytic/StressValue.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/dof/DOFS.h>
#include "Computable.h"
#include <feamy/integration/integrables/StiffnessMatrixIntegrable.h>
#include <veamy/utilities/veamy_functions.h>
#include <feamy/models/FeamyElement.h>


/*
 * Computes the term (sigma - sigmaH)*(epsilon - epsilonH) of the H1 norm. As VEM does not use shape functions,
 * this computable is exclusively used in FEM-like methods
 */
template <typename T>
class StrainStressDifferenceComputable : public Computable<T>{
private:
    /*
     * Analytical strain and stress values
     */
    StrainValue* strainValue;
    StressValue* stressValue;

    /*
     * Nodal displacement values
     */
    Eigen::VectorXd nodalValues;

    /*
     * Material (strain/stress) matrix
     */
    Eigen::MatrixXd C;

    /*
     * Degrees of freedom of the system
     */
    DOFS dofs;

    /*
     * Elements of the system
     */
    std::vector<FeamyElement*> elements;

    /*
     * Mesh points
     */
    std::vector<Point> points;

    /*
     * Index of the polygon that contains the points that will be used next
     */
    int polygonIndex;
public:
    /*
     * Constructor
     */
    StrainStressDifferenceComputable(StrainValue *strain, StressValue *stress,
                                     Eigen::VectorXd u, DOFS d, std::vector<FeamyElement*> elements,
                                     std::vector<Point> p, Eigen::MatrixXd C);

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