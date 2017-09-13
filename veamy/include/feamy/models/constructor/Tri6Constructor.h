#ifndef VEAMY_TRI6CONSTRUCTOR_H
#define VEAMY_TRI6CONSTRUCTOR_H

#include <feamy/models/constructor/FemElementConstructor.h>

class Tri6Constructor : public FemElementConstructor{
public:
    FemElement* createElement(Conditions conditions, Triangle t, UniqueList<Point>& points, DOFS& out);
};

#endif