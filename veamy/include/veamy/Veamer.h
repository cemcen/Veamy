#ifndef VEAMY_VEAMER_H
#define VEAMY_VEAMER_H

#include <delynoi/models/Mesh.h>
#include <veamy/models/dof/DOFS.h>
#include <veamy/models/constraints/EssentialConstraints.h>
#include <veamy/models/VemElement.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/physics/Conditions.h>
#include <iostream>
#include "Calculator2D.h"
#include <utilities/utilities.h>


struct PolygonHasher {
    std::size_t operator()(const Polygon &k) const {
        using std::size_t;
        using std::hash;

        return k.hash;
    }
};


class Veamer : public Calculator2D<Polygon> {
public:
    std::vector<VemElement> elements;
    Veamer();

    Mesh<Polygon> initProblemFromFile(std::string fileName, Material* material);
    Mesh<Polygon> initProblemFromFile(std::string fileName, Material* material, BodyForce *force);
    void initProblem(Mesh<Polygon> m, Conditions conditions);
    void createAndAssemble(Eigen::MatrixXd& KGlobal, Eigen::VectorXd& fGlobal);

    double computeErrorNorm(NormCalculator* calculator, Mesh<Polygon> mesh);
};


#endif
