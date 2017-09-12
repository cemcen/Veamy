#ifndef VEAMY_NONE_H
#define VEAMY_NONE_H

#include <veamy/physics/body forces/ConstantBodyForce.h>

class None : public ConstantBodyForce{
public:
    double applyX(double x, double y){
        return 0;
    }

    double applyY(double x, double y){
        return 0;
    }
};

#endif