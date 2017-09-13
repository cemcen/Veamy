#ifndef VEAMY_FEAMER_H
#define VEAMY_FEAMER_H

#include <veamy/Calculator2D.h>
#include <veamy/physics/bodyforces/BodyForce.h>
#include <delynoi/models/polygon/Triangle.h>
#include <veamy/lib/Eigen/Dense>
#include <feamy/models/FemElement.h>
#include <feamy/models/constructor/FemElementConstructor.h>

class Feamer : public Calculator2D<Triangle>{
private:
    std::vector<FemElement*> elements;
public:
    void initProblem(Mesh<Triangle> m, Conditions conditions, FemElementConstructor* constructor);
    void createAndAssemble(Eigen::MatrixXd& KGlobal, Eigen::VectorXd& fGlobal);
};

#endif