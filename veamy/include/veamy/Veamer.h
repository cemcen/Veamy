#ifndef VEAMY_VEAMER_H
#define VEAMY_VEAMER_H

#include <delynoi/models/Mesh.h>
#include <veamy/models/dof/DOFS.h>
#include <veamy/models/constraints/EssentialConstraints.h>
#include <veamy/models/VemElement.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/physics/VeamyConditions.h>
#include <iostream>
#include "Calculator2D.h"


struct PolygonHasher {
    std::size_t operator()(const Polygon &k) const {
        using std::size_t;
        using std::hash;

        return k.hash;
    }
};

class Veamer : public Calculator2D {
protected:
    virtual void createElement(Polygon p);
public:
    std::vector<VemElement> elements;
    Veamer();

    Mesh<Polygon> initProblemFromFile(std::string fileName, Material* material);
    Mesh<Polygon> initProblemFromFile(std::string fileName, Material* material, VeamyBodyForce *force);
    void initProblem(Mesh<Polygon> m, VeamyConditions conditions);
    void createAndAssemble(Eigen::MatrixXd& KGlobal, Eigen::VectorXd& fGlobal);
};


#endif
