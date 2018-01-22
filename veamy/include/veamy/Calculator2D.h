#ifndef VEAMY_CALCULATOR2D_H
#define VEAMY_CALCULATOR2D_H

#include <utilities/UniqueList.h>
#include <veamy/physics/conditions/Conditions.h>
#include <veamy/models/dof/DOFS.h>
#include <veamy/problems/ProblemDiscretization.h>
#include <veamy/models/Element.h>
#include <veamy/lib/Eigen/Sparse>

/*
 * Abstract class that encapsulates all common behaviour for linear elasticity calculations, no matter the method
 * used
 */
template <typename T>
class Calculator2D {
protected:
    /*
     * Elements of the system
     */
    std::vector<Element<T>*> elements;

    /*
     * Conditions of the problem to solve
     */
    Conditions* conditions;

    /*
     * Mesh points
     */
    UniqueList<Point> points;

    /*
     *
     */
    void fromDenseToSparse(Eigen::MatrixXd& K, std::vector<Eigen::Triplet<double>>& coeffs);
public:
    /*
     * Degrees of freedom of the system
     */
    DOFS DOFs;

    Calculator2D(Conditions* conditions, int n_dofs);

    /* Gets the degrees of freedom indexes related to a point
     * @param point_index point to lookup
     * @return dofs related to the given point
     */
    std::vector<int> pointToDOFS(int point_index);

    /*
     * @return mesh points
     */
    UniqueList<Point> getPoints() const;

    /*
     * @return mesh points
     */
    UniqueList<Point> getPoints();

    /* Assembles the global stiffness matrix and load vector
     * @param Kglobal global stiffness matrix
     * @param fGlobal global load vector
     */
    void assemble(Eigen::MatrixXd &Kglobal, Eigen::VectorXd &fGlobal);

    /* Creates the global stiffness matrix and load vector, imposes the essential boundary conditions on the system and
     * solves the problem
     * @param mesh domain of the problem
     * @return computed displacements
     */
    Eigen::VectorXd simulate(Mesh<T> &mesh);

    /* Writes the computed nodal displacements to a text file
     * @param fileName name of the file to write the displacements to
     * @param u computed displacements
     */
    void writeDisplacements(std::string fileName, Eigen::VectorXd u);
};

#endif