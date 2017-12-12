#ifndef VEAMY_ELEMENT_H
#define VEAMY_ELEMENT_H

#include <veamy/lib/Eigen/Dense>
#include <veamy/models/dof/DOFS.h>
#include <veamy/physics/Conditions.h>
#include <veamy/physics/traction/TractionVector.h>
#include <veamy/physics/bodyforces/BodyForceVector.h>

/*
 * Class that models a generic element of a problem
 */
template <typename T>
class Element {
protected:
    /*
     * List of the indexes of the degrees of freedom of the element
     */
    std::vector<int> dofs;

    /*
     * Geometric equivalent of the element (Polygon, Triangle, etc)
     */
    T p;

    /*
     * Elemental load vector and stiffness matrix
     */
    Eigen::VectorXd f;
    Eigen::MatrixXd K;
public:
    /*
     * Creates the element from the problem conditions and the geometry
     * @param conditions
     */
    void initializeElement(Conditions &conditions, T &p, UniqueList<Point> &points, DOFS &out);
    T getAssociatedPolygon();
    void assemble(DOFS out, Eigen::MatrixXd &Kglobal, Eigen::VectorXd &Fglobal);
    void computeF(DOFS d, UniqueList<Point> points, Conditions &conditions, BodyForceVector* bodyForceVector,
                  TractionVector* tractionVector);
};

#endif