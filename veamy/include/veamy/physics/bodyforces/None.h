#ifndef VEAMY_NONE_H
#define VEAMY_NONE_H

#include <veamy/physics/bodyforces/BodyForce.h>

class None : public BodyForce{
public:
    double applyX(double x, double y){
        return 0;
    }

    double applyY(double x, double y){
        return 0;
    }
};

#endif