#include <veamy/models/constraints/EssentialConstraints.h>

EssentialConstraints::EssentialConstraints() {}

Eigen::VectorXd EssentialConstraints::getBoundaryValues(std::vector<Point> points, UniqueList<DOF> dofs) {
    Eigen::VectorXd values;
    values = Eigen::VectorXd::Zero(constrained_dofs.size());

    for (int i = 0; i < constrained_dofs.size(); ++i){
        Constraint constraintI = constraints_map[constrained_dofs[i]];
        DOF dofI = dofs[constrained_dofs[i]];

        double val = constraintI.getValue(points[dofI.pointIndex()]);
        values(i) = val;
    }

    return values;
}



