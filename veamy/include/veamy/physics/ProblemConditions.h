#ifndef THESIS_PROBLEMCONDITIONS_H
#define THESIS_PROBLEMCONDITIONS_H

#include <veamy/physics/VariableBodyForce.h>
#include <veamy/physics/Material.h>
#include <veamy/physics/body forces/None.h>

struct ProblemConditions{
    ConstraintsContainer constraints;
    BodyForce* f;
    Material* material;

    ProblemConditions(ConstraintsContainer container, BodyForce* bodyForce, Material* mat){
        constraints = container;
        f = bodyForce;
        material = mat;
    }

    ProblemConditions(ConstraintsContainer container, Material* mat){
        constraints = container;
        f = new None();
        material = mat;
    }

    ProblemConditions(){};
};


#endif 
