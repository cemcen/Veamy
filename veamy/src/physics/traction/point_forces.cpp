#include <veamy/models/constraints/structures/isConstrainedInfo.h>
#include <veamy/models/constraints/PointConstraint.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/constraints/NaturalConstraints.h>

namespace point_forces{
    void addPointForces(Eigen::VectorXd& tractionVector, NaturalConstraints natural, Point p1, Point p2){
        isConstrainedInfo isConstrainedInfoP1 = natural.isConstrainedByPoint(p1);
        isConstrainedInfo isConstrainedInfoP2 = natural.isConstrainedByPoint(p2);

        if(isConstrainedInfoP1.isConstrained){
            std::vector<PointConstraint> constraints = natural.getConstraintInformation(p1);

            for (Constraint c: constraints){
                tractionVector(0) += c.getValue(p1)*c.isAffected(DOF::Axis::x);
                tractionVector(1) += c.getValue(p1)*c.isAffected(DOF::Axis::y);
            }
        }

        if(isConstrainedInfoP2.isConstrained){
            std::vector<PointConstraint> constraints = natural.getConstraintInformation(p2);

            for (Constraint c: constraints){
                tractionVector(2) += c.getValue(p2)*c.isAffected(DOF::Axis::x);
                tractionVector(3) += c.getValue(p2)*c.isAffected(DOF::Axis::y);
            }
        }

    }
}