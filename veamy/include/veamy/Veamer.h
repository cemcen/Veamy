#ifndef VEAMY_VEAMER_H
#define VEAMY_VEAMER_H

#include <mesher/models/PolygonalMesh.h>
#include <veamy/models/dof/DOFS.h>
#include <veamy/models/constraints/EssentialConstraints.h>
#include <veamy/models/Element.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/physics/ProblemConditions.h>
#include <iostream>


struct PolygonHasher {
    std::size_t operator()(const Polygon &k) const {
        using std::size_t;
        using std::hash;

        return k.hash;
    }
};

class Veamer {
protected:
    ProblemConditions conditions;
    UniqueList<Point> points;

    virtual void createElement(Polygon p);
    void insertElement(Polygon p, int index);
public:
    DOFS DOFs;
    std::vector<Element> elements;
    Veamer();

    void initProblemFromFile(std::string fileName, Material material);
    void initProblemFromFile(std::string fileName, Material material, BodyForce* force);
    void initProblem(PolygonalMesh m, ProblemConditions conditions);
    Eigen::VectorXd simulate(PolygonalMesh &mesh);

    Pair<int> pointToDOFS(int point_index);
    Material getMaterial();
    UniqueList<Point> getPoints() const;
    UniqueList<Point> getPoints();
    ProblemConditions getConditions() const;

    void writeDisplacements(std::string fileName, Eigen::VectorXd u);
};


#endif
