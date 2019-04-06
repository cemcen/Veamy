#include <veamy/models/constraints/structures/isConstrainedInfo.h>
#include <veamy/models/constraints/PointConstraint.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/constraints/NaturalConstraints.h>

namespace point_forces{
    void addPointForces(Eigen::VectorXd &tractionVector, NaturalConstraints &natural, Point p1, Point p2, int n_dofs) {
        isConstrainedInfo isConstrainedInfoP1 = natural.isConstrainedByPoint(p1);
        isConstrainedInfo isConstrainedInfoP2 = natural.isConstrainedByPoint(p2);

        if(isConstrainedInfoP1.isConstrained){
            std::vector<PointConstraint> constraints = natural.getConstraintInformation(p1);

            for (Constraint c: constraints){
                for (int i = 0; i < n_dofs; ++i) {
                    tractionVector(i) += c.getValue(p1)*c.isAffected(i);
                }
            }
        }

        if(isConstrainedInfoP2.isConstrained){
            std::vector<PointConstraint> constraints = natural.getConstraintInformation(p2);

            for (Constraint c: constraints){
                for (int i = 0; i < n_dofs; ++i) {
                    tractionVector(n_dofs + i) += c.getValue(p2)*c.isAffected(i);
                }
            }
        }

    }
}