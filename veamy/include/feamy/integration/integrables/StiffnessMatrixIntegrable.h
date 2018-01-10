#ifndef VEAMY_STIFFNESSMATRIXINTEGRABLE_H
#define VEAMY_STIFFNESSMATRIXINTEGRABLE_H

#include <veamy/lib/Eigen/Dense>
#include <feamy/integration/IntegrableFunction.h>
#include <veamy/geometry/VeamyTriangle.h>
#include <feamy/models/shapefunctions/ShapeFunctions.h>

/*
 * Represents the function that needs to be integrated related to the FEM stiffness matrix (derivatives of the
 * shape functions)
 */
class StiffnessMatrixIntegrable : public IntegrableFunction<Eigen::MatrixXd>{
protected:
    /*
     * Shape functions of the element
     */
    ShapeFunctions* N;

    /*
     * Jacobian matrix of the element geometry
     */
    Eigen::MatrixXd J;
public:
    /*
     * Constructor
     */
    StiffnessMatrixIntegrable(VeamyTriangle &t, std::vector<Point> &points){
        this->J = t.getJacobian(points);
    }

    /*
     * Default constructor
     */
    StiffnessMatrixIntegrable(){}

    /*
     * Computes the value of the function at a given point
     * @param p point where the function must be evaluated
     * @return value of the (dNi, dNj) function that represents the stiffness matrix
     */
    virtual Eigen::MatrixXd apply(Point p) = 0;

    /*
     * Computes the Be matrix of the element
     * @param p point where the matrix is computed
     * @param J jacobian matrix of the element
     * @param N shape functions of the element
     * @return the Be FEM matrix
     */
    virtual Eigen::MatrixXd BeMatrix(Point p, Eigen::MatrixXd J, ShapeFunctions* N) = 0;

    /* Sets the value of the shape functions of the element
     * @param s shape functions
     */
    void setShapeFunctions(ShapeFunctions* N){
        this->N = N;
    }
};

#endif