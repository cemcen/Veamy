#ifndef VEAMY_ELEMENT_H
#define VEAMY_ELEMENT_H

#include <veamy/lib/Eigen/Dense>
#include <veamy/models/dof/DOFS.h>
#include <veamy/physics/VeamyConditions.h>

template <typename T>
class Element {
protected:
    std::vector<int> dofs;
    T p;

    Eigen::VectorXd f;
    Eigen::MatrixXd K;
public:
    void initializeElement(VeamyConditions &conditions, T &p, UniqueList<Point> &points, DOFS &out);
    T getAssociatedPolygon();
    void assemble(DOFS out, Eigen::MatrixXd &Kglobal, Eigen::VectorXd &Fglobal);
};

#endif