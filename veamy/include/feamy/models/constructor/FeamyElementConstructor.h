#ifndef VEAMY_FEMELEMENTCONSTRUCTOR_H
#define VEAMY_FEMELEMENTCONSTRUCTOR_H

#include <feamy/models/FeamyElement.h>

class FeamyElementConstructor{
public:
    virtual FeamyElement* createElement(Conditions& conditions, Triangle t, UniqueList<Point>& points, DOFS& out) = 0;
};

#endif