#ifndef VEAMY_TRI3CONSTRUCTOR_H
#define VEAMY_TRI3CONSTRUCTOR_H

#include "FeamyElementConstructor.h"

class Tri3Constructor : public FeamyElementConstructor{
public:
    FeamyElement* createElement(Conditions& conditions, Triangle t, UniqueList<Point>& points, DOFS& out);
};

#endif