#ifndef VEAMY_NONE_H
#define VEAMY_NONE_H

#include <veamy/physics/bodyforces/BodyForce.h>
#include <veamy/utilities/veamy_functions.h>

/*
 * Concrete BodyForce implementation that models the non existance of a body force (it returns zero always)
 */
class None : public BodyForce{
public:
    /*
     * Constructor. Assigns none functions (just return 0) to each axis function
     */
    None(){
        this->fX = new FunctionComputable(&veamy_functions::none_function);
        this->fY = new FunctionComputable(&veamy_functions::none_function);
    }
};

#endif