#ifndef VEAMY_TRI3CONSTRUCTOR_H
#define VEAMY_TRI3CONSTRUCTOR_H

#include "FemElementConstructor.h"

class Tri3Constructor : public FemElementConstructor{
public:
    FemElement* createElement(Conditions& conditions, Triangle t, UniqueList<Point>& points, DOFS& out);
};

#endif