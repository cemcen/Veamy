#ifndef VEAMY_FEMELEMENT_H
#define VEAMY_FEMELEMENT_H

#include <delynoi/models/polygon/Triangle.h>
#include <veamy/physics/Conditions.h>
#include <veamy/models/Element.h>
#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <vector>
#include <feamy/integration/AreaIntegrator.h>
#include <feamy/integration/integrables/BodyForceIntegrable.h>
#include <veamy/physics/bodyforces/BodyForceVector.h>
#include <feamy/physics/FeamyBodyForceVector.h>
#include <feamy/physics/FeamyTractionVector.h>
#include <veamy/geometry/VeamyTriangle.h>
#include <feamy/integration/integrables/StiffnessMatrixIntegrable.h>

/*
 * Base class from which all FEM elements inherit. It encapsulates the common behaviour of all elements.
 */
class FeamyElement: public Element<Triangle> {
protected:
    /*
     * Shape functions of the element
     */
    ShapeFunctions* N;
public:
    /*
     * Constructor
     */
    FeamyElement();

    /*
     * Sets the shape functions and initializes all parameters of the element
     * @param conditions conditions of the problem
     * @param p triangle related to the element
     * @param points mesh points
     * @param out degrees of freedom of the system
     * @param N shape functions of the element
     */
    void initializeElement(Conditions &conditions, Triangle &p, UniqueList<Point> &points, DOFS &out, ShapeFunctions* N);

    /* Computes the elemental stiffness matrix
      * @param d degrees of freedom of the system
      * @param points mesh points
      * @param conditions conditions of the problem
      */
    void computeK(DOFS d, UniqueList<Point> points, Conditions &conditions);

    /* Computes the elemental load vector
    * @param d degrees of freedom of the system
    * @param points mesh points
    * @param conditions conditions of the problem
    */
    void computeF(DOFS d, UniqueList<Point> points, Conditions& conditions);

    /*
     * @return shape functions of the element
     */
    ShapeFunctions* getShapeFunctions();
};

#endif