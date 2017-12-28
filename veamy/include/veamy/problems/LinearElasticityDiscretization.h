#ifndef VEAMY_LINEARELASTICITYDISCRETIZATION_H
#define VEAMY_LINEARELASTICITYDISCRETIZATION_H

#include <veamy/physics/conditions/LinearElasticityConditions.h>
#include <veamy/models/Element.h>
#include "ProblemDiscretization.h"

class LinearElasticityDiscretization : public ProblemDiscretization{
public:
    LinearElasticityConditions* conditions;

    LinearElasticityDiscretization(LinearElasticityConditions* conditions);
    Element* createElement(Veamer *v, Polygon &poly, UniqueList<Point> &points);
    Element* createElement(Feamer *f, Triangle &poly, UniqueList<Point> &points);

    Mesh<Polygon> initProblemFromFile(Veamer *v, std::string fileName);
};

#endif