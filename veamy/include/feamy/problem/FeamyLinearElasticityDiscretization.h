#ifndef VEAMY_FEAMYLINEARELASTICITYDISCRETIZATION_H
#define VEAMY_FEAMYLINEARELASTICITYDISCRETIZATION_H

#include <feamy/Feamer.h>
#include <delynoi/models/polygon/Triangle.h>
#include <veamy/physics/conditions/LinearElasticityConditions.h>

class FeamyLinearElasticityDiscretization : public ProblemDiscretization<Triangle,Feamer>{
public:
    LinearElasticityConditions* conditions;

    FeamyLinearElasticityDiscretization(LinearElasticityConditions* conditions);
    Element<Triangle>* createElement(Feamer *f, Triangle &poly, UniqueList<Point> &points);

    Mesh<Triangle> initProblemFromFile(Feamer *f, std::string fileName);
};

#endif