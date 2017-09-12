#ifndef VEAMY_CONDITIONS_H
#define VEAMY_CONDITIONS_H

#include <veamy/physics/body forces/VeamyBodyForce.h>

template <typename T>
struct Conditions{
    ConstraintsContainer constraints;
    T* f;
    Material* material;

    Conditions(ConstraintsContainer container, T* bodyForce, Material* mat){
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

template class Conditions<VeamyBodyForce>;
template class Conditions<BodyForce>;

#endif