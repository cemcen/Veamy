#ifndef VEAMY_FEAMER_H
#define VEAMY_FEAMER_H

#include <veamy/Calculator2D.h>
#include <veamy/physics/bodyforces/BodyForce.h>
#include <delynoi/models/polygon/Triangle.h>
#include <veamy/lib/Eigen/Dense>
#include <feamy/models/FeamyElement.h>
#include <feamy/models/constructor/FeamyElementConstructor.h>
#include <veamy/postprocess/NormCalculator.h>

class Feamer : public Calculator2D<Triangle>{
private:
    std::vector<FeamyElement*> elements;
public:
    Feamer();

    void initProblem(Mesh<Triangle> m, Conditions conditions, FeamyElementConstructor* constructor);
    void assemble(Eigen::MatrixXd& KGlobal, Eigen::VectorXd& fGlobal);
    double computeErrorNorm(NormCalculator<Triangle>* calculator, Mesh<Triangle> mesh);
};

#endif