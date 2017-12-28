#ifndef VEAMY_POISSONDISCRETIZATION_H
#define VEAMY_POISSONDISCRETIZATION_H

#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/physics/conditions/PoissonConditions.h>
#include "ProblemDiscretization.h"

class PoissonDiscretization : public ProblemDiscretization{
public:
    PoissonConditions* conditions;

    PoissonDiscretization(PoissonConditions* conditions);
    Element* createElement(Veamer *v, Polygon &poly, UniqueList<Point> &points);
    Element* createElement(Feamer *f, Triangle &poly, UniqueList<Point> &points);


};

#endif