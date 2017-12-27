#ifndef VEAMY_CONDITIONS_H
#define VEAMY_CONDITIONS_H

#include <veamy/physics/bodyforces/BodyForce.h>
#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/physics/materials/Material.h>
#include <veamy/physics/bodyforces/None.h>


class Conditions{
public:
    /*
     * Conditions of the problem
     */
    ConstraintsContainer constraints;
    BodyForce* f;

    /*
     * Constructor
     */
    Conditions(ConstraintsContainer container, BodyForce* bodyForce){
        constraints = container;
        f = bodyForce;
    }

    /*
     * Default constructor
     */
    Conditions(){};

};


#endif