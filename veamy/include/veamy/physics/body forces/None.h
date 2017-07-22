#ifndef THESIS_NONE_H
#define THESIS_NONE_H

#include <veamy/physics/ConstantBodyForce.h>

class None : public ConstantBodyForce{
private:
    double applyX(double x, double y){
        return 0;
    }

    double applyY(double x, double y){
        return 0;
    }
};

#endif