#ifndef VEAMY_INTEGRABLEFUNCTION_H
#define VEAMY_INTEGRABLEFUNCTION_H

#include <delynoi/models/basic/Point.h>
#include <veamy/geometry/VeamyTriangle.h>

template <typename S>
class IntegrableFunction{
public:
    virtual S apply(Point p) = 0;

    virtual S apply(Point p, VeamyTriangle container){
        return this->apply(p);
    }
};

#endif