#ifndef VEAMY_CONDITIONS_H
#define VEAMY_CONDITIONS_H

#include <veamy/physics/bodyforces/BodyForce.h>
#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/physics/materials/Material.h>
#include <veamy/physics/bodyforces/None.h>

struct Conditions{
    ConstraintsContainer constraints;
    BodyForce* f;
    Material* material;

    Conditions(ConstraintsContainer container, BodyForce* bodyForce, Material* mat){
        constraints = container;
        f = bodyForce;
        material = mat;
    }

    Conditions(ConstraintsContainer container, Material* mat){
        constraints = container;
        f = new None();
        material = mat;
    }

    Conditions(){};

};


#endif