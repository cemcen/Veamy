#ifndef VEAMY_CALCULATOR2D_H
#define VEAMY_CALCULATOR2D_H

template <typename ...> class Calculator2D;

template <typename T, typename S>
class Calculator2D {
protected:
    Conditions<S> conditions;
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