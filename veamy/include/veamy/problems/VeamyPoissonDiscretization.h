#ifndef VEAMY_POISSONDISCRETIZATION_H
#define VEAMY_POISSONDISCRETIZATION_H

#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/physics/conditions/PoissonConditions.h>
#include <veamy/Veamer.h>
#include "ProblemDiscretization.h"

/*
 * Class that
 */
class VeamyPoissonDiscretization : public ProblemDiscretization<Polygon,Veamer>{
public:
    PoissonConditions* conditions;

    VeamyPoissonDiscretization(PoissonConditions* conditions);
    Element<Polygon>* createElement(Veamer *v, Polygon &poly, UniqueList<Point> &points);
    Mesh<Polygon> initProblemFromFile(Veamer *v, std::string fileName);
};

#endif