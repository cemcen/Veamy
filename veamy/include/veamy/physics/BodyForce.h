#ifndef THESIS_BODYFORCE_H
#define THESIS_BODYFORCE_H

#include <veamy/models/dof/DOF.h>

class BodyForce {
public:
    virtual double apply(double x, double y) = 0;
    virtual double isApplicable(double result, DOF::Axis axis){
        return result;
    };
};


#endif
