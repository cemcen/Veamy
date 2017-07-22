#ifndef VEAMY_ELEMENT_H
#define VEAMY_ELEMENT_H

#include <veamy/models/dof/DOF.h>
#include <veamy/models/dof/DOFS.h>
#include <mesher/models/polygon/Polygon.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/utilities/SegmentPair.h>
#include <veamy/physics/VariableBodyForce.h>
#include <iostream>
#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/physics/ProblemConditions.h>
#include <veamy/models/Edge.h>
#include <veamy/physics/Material.h>
#include <veamy/physics/BodyForceVector.h>

class Element {
private:
    std::vector<int> dofs;
    Polygon p;
    Eigen::MatrixXd K;
    Eigen::VectorXd f;
public:
    Element(ProblemConditions &conditions, Polygon &p, UniqueList<Point> &points, DOFS &out);
    void assemble(DOFS out, Eigen::MatrixXd& Kglobal,  Eigen::VectorXd& Fglobal);
    void computeK(DOFS d, UniqueList<Point> points, ProblemConditions &conditions);
    void computeF(DOFS d, UniqueList<Point> points, ProblemConditions &conditions);
    Polygon getAssociatedPolygon();
};


#endif
