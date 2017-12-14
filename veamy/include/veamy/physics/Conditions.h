#ifndef VEAMY_CONDITIONS_H
#define VEAMY_CONDITIONS_H

#include <veamy/physics/bodyforces/BodyForce.h>
#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/physics/materials/Material.h>
#include <veamy/physics/bodyforces/None.h>

/*
 * Structure that contains the conditions of a linear elasticity problem, including the boundary conditions,
 * the bodyforce and the material of the domain
 */
struct Conditions{
    /*
     * Conditions of the linear elasticity problem
     */
    ConstraintsContainer constraints;
    BodyForce* f;
    Material* material;

    /*
     * Constructor
     */
    Conditions(ConstraintsContainer container, BodyForce* bodyForce, Material* mat){
        constraints = container;
        f = bodyForce;
        material = mat;
    }

    /*
     * Constructor. Does not include a body force, so the default option (None) is set
     */
    Conditions(ConstraintsContainer container, Material* mat){
        constraints = container;
        f = new None();
        material = mat;
    }

    /*
     * Default constructor
     */
    Conditions(){};

};


#endif