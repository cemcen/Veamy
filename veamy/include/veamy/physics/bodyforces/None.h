#ifndef VEAMY_NONE_H
#define VEAMY_NONE_H

#include <veamy/physics/bodyforces/BodyForce.h>

double f(double x, double y){
    return 0;
}

class None : public BodyForce{
public:
    None(){
        this->fX = &f;
        this->fY = &f;
    }
};

#endif