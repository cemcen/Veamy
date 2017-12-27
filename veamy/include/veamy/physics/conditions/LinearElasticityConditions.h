#ifndef VEAMY_LINEARELASTICITYCONDITIONS_H
#define VEAMY_LINEARELASTICITYCONDITIONS_H

#include "Conditions.h"

/*
 * Class that contains the conditions unique to a linear elasticity problem (material matrix)
 */
class LinearElasticityConditions : public Conditions{
public:
    /*
     * Material properties of the domain
     */
    Material* material;

    /*
     * Constructor
     */
    LinearElasticityConditions(ConstraintsContainer container, BodyForce* f, Material* mat) :
            Conditions(container, f){
        this->material = mat;
    }

    /*
     * Constructor. As a body force is not given, the default value is used
     */
    LinearElasticityConditions(ConstraintsContainer container, Material* mat) :
            Conditions(container, new None(0,0)){
        this->material = mat;
    }

};

#endif