#ifndef VEAMY_FEAMYLINEARELASTICITYDISCRETIZATION_H
#define VEAMY_FEAMYLINEARELASTICITYDISCRETIZATION_H

#include <feamy/Feamer.h>
#include <delynoi/models/polygon/Triangle.h>
#include <veamy/physics/conditions/LinearElasticityConditions.h>

/*
 * Class that model the resolution of the linear elasticity
 */
class FeamyLinearElasticityDiscretization : public ProblemDiscretization<Triangle,Feamer>{
public:
    LinearElasticityConditions* conditions;

    FeamyLinearElasticityDiscretization(LinearElasticityConditions* conditions);
    Element<Triangle>* createElement(Feamer *f, Triangle &poly, UniqueList<Point> &points);

    Mesh<Triangle> initProblemFromFile(Feamer *f, std::string fileName);
    NormResult computeErrorNorm(NormCalculator<Triangle> *calculator, Mesh<Triangle> mesh, Feamer* f);
};

#endif