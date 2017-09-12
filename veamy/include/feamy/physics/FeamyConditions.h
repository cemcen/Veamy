#ifndef VEAMY_FEAMYCONDITIONS_H
#define VEAMY_FEAMYCONDITIONS_H

#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/physics/body forces/BodyForce.h>
#include <veamy/physics/materials/Material.h>
#include <feamy/physics/body forces/None.h>
#include <veamy/physics/Conditions.h>

struct VeamyConditions : Conditions{
    ConstraintsContainer constraints;
    BodyForce* f;
    Material* material;

    VeamyConditions(ConstraintsContainer container, BodyForce* bodyForce, Material* mat){
        constraints = container;
        f = bodyForce;
        material = mat;
    }

    VeamyConditions(ConstraintsContainer container, Material* mat){
        constraints = container;
        f = new None();
        material = mat;
    }

    VeamyConditions(){};
};

#endif