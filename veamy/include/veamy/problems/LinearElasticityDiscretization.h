#ifndef VEAMY_LINEARELASTICITYDISCRETIZATION_H
#define VEAMY_LINEARELASTICITYDISCRETIZATION_H

#include <veamy/physics/conditions/LinearElasticityConditions.h>
#include "ProblemDiscretization.h"
#include "VectorialProblem.h"

class LinearElasticityDiscretization : public ProblemDiscretization, VectorialProblem{
public:


    LinearElasticityConditions* conditions;
};

#endif