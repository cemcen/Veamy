#ifndef FEAMY_NONE_H
#define FEAMY_NONE_H

#include <veamy/physics/body forces/BodyForce.h>

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