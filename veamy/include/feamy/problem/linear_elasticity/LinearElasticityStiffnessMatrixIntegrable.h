#ifndef VEAMY_LINEARELASTICITYSTIFFNESSMATRIXINTEGRABLE_H
#define VEAMY_LINEARELASTICITYSTIFFNESSMATRIXINTEGRABLE_H

#include <veamy/lib/Eigen/Dense>
#include <feamy/integration/IntegrableFunction.h>
#include <veamy/geometry/VeamyTriangle.h>
#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <feamy/integration/integrables/StiffnessMatrixIntegrable.h>

/*
 * Represents the function that needs to be integrated related to the FEM stiffness matrix (derivatives of the
 * shape functions)
 */
class LinearElasticityStiffnessMatrixIntegrable : public StiffnessMatrixIntegrable{
private:
    /*
     * Shape functions of the element
     */
    ShapeFunctions* N;

    /*
     * Jacobian matrix of the element geometry
     */
    Eigen::MatrixXd J;

    /*
     * Material matrix
     */
    Eigen::MatrixXd D;
public:
    /*
     * Constructor
     */
    LinearElasticityStiffnessMatrixIntegrable(VeamyTriangle &t, std::vector<Point> &points, Eigen::MatrixXd D);

    /*
     * Default constructor
     */
    LinearElasticityStiffnessMatrixIntegrable();

    /*
     * Computes the value of the function at a given point
     * @param p point where the function must be evaluated
     * @return value of the (dNi, dNj) function that represents the stiffness matrix
     */
    Eigen::MatrixXd apply(Point p);

    /*
     * Computes the Be matrix of the element
     * @param p point where the matrix is computed
     * @param J jacobian matrix of the element
     * @param N shape functions of the element
     * @return the Be FEM matrix
     */
    Eigen::MatrixXd BeMatrix(Point p, Eigen::MatrixXd J, ShapeFunctions* N);
};

#endif