#ifndef VEAMY_CALCULATOR2D_H
#define VEAMY_CALCULATOR2D_H

#include <utilities/UniqueList.h>
#include <veamy/physics/Conditions.h>
#include <veamy/models/dof/DOFS.h>


template <typename T>
class Calculator2D {
protected:
    Conditions conditions;
    UniqueList<Point> points;
public:
    DOFS DOFs;

    Pair<int> pointToDOFS(int point_index);
    Material* getMaterial();
    UniqueList<Point> getPoints() const;
    UniqueList<Point> getPoints();

    virtual void createAndAssemble(Eigen::MatrixXd& Kglobal, Eigen::VectorXd& fGlobal) = 0;
    Eigen::VectorXd simulate(Mesh<T> &mesh);
    void writeDisplacements(std::string fileName, Eigen::VectorXd u);
};

#endif