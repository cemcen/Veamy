#ifndef VEAMY_FEMELEMENTCONSTRUCTOR_H
#define VEAMY_FEMELEMENTCONSTRUCTOR_H

#include <feamy/models/FemElement.h>

class FemElementConstructor{
public:
    virtual FemElement* createElement(Conditions conditions, Triangle t, UniqueList<Point>& points, DOFS& out) = 0;
};

#endif