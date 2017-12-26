#ifndef VEAMY_POISSONDISCRETIZATION_H
#define VEAMY_POISSONDISCRETIZATION_H

#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/physics/conditions/PoissonConditions.h>
#include "ProblemDiscretization.h"
#include "ScalarProblem.h"

class PoissonDiscretization : public ProblemDiscretization, ScalarProblem{
public:
    PoissonConditions conditions;

    PoissonDiscretization();
};

#endif