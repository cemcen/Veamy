#ifndef VEAMY_POISSONCONDITIONS_H
#define VEAMY_POISSONCONDITIONS_H

#include "Conditions.h"

/*
 * Class that contains the conditions of the Poisson problem
 */
class PoissonConditions : public Conditions{
public:
    /*
     * Constructor
     */
    PoissonConditions(ConstraintsContainer container, BodyForce* f);

    /*
     * Constructor. As a body force is not given, the default value is used
     */
    PoissonConditions(ConstraintsContainer container);


};

#endif