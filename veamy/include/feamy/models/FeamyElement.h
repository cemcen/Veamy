#ifndef VEAMY_FEMELEMENT_H
#define VEAMY_FEMELEMENT_H

#include <delynoi/models/polygon/Triangle.h>
#include <veamy/physics/conditions/Conditions.h>
#include <veamy/models/Element.h>
#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <vector>
#include <feamy/integration/AreaIntegrator.h>
#include <veamy/physics/bodyforces/BodyForceVector.h>
#include <feamy/physics/FeamyBodyForceVector.h>
#include <feamy/physics/FeamyTractionVector.h>
#include <veamy/geometry/VeamyTriangle.h>
#include <feamy/integration/integrables/BodyForceIntegrable.h>
#include <feamy/integration/integrables/BoundaryVectorIntegrable.h>
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

    /*
     * Calculates the value related to the body force part of the equation (right hand side)
     */
    BodyForceIntegrable* bodyForceIntegrable;

    /*
     * Calculates the value related to the external loads
     */
    BoundaryVectorIntegrable* boundaryVectorIntegrable;

    /*
     * Calculates the stiffness matrix inner value (that is integrated)
     */
    StiffnessMatrixIntegrable* stiffnessMatrixIntegrable;
public:
    /*
     * Constructor
     */
    FeamyElement(Conditions *conditions, Triangle &p, UniqueList<Point> &points, DOFS &out, int n_dofs);

    /*
     * Sets the shape functions of this element
     * @param N shape functions
     */
    void setShapeFunctions(ShapeFunctions* N);

    /* Sets the integrable classes used to compute the stiffness matrix and load vector
     * @param bodyForceIntegrable class in charge of computing the
     * @param
     */
    void setIntegrables(BodyForceIntegrable* bodyForceIntegrable, BoundaryVectorIntegrable* boundaryVectorIntegrable,
                        StiffnessMatrixIntegrable* stiffnessMatrixIntegrable);

    /* Computes the elemental stiffness matrix
      * @param d degrees of freedom of the system
      * @param points mesh points
      * @param conditions conditions of the problem
      */
    void computeK(DOFS &d, UniqueList<Point> &points);

    /* Computes the elemental load vector
    * @param d degrees of freedom of the system
    * @param points mesh points
    * @param conditions conditions of the problem
    */
    void computeF(DOFS &d, UniqueList<Point> &points, Conditions *conditions);

    /*
     * @return shape functions of the element
     */
    ShapeFunctions* getShapeFunctions();
};

#endif