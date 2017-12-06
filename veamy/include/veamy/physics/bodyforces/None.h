#ifndef VEAMY_NONE_H
#define VEAMY_NONE_H

#include <veamy/physics/bodyforces/BodyForce.h>
#include <veamy/utilities/veamy_functions.h>

class None : public BodyForce{
public:
    None(){
        this->fX = new FunctionComputable(&veamy_functions::none_function);
        this->fY = new FunctionComputable(&veamy_functions::none_function);
    }
};

#endif