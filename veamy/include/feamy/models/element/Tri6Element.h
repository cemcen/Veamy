#ifndef VEAMY_TRI6ELEMENT_H
#define VEAMY_TRI6ELEMENT_H

#include <feamy/models/FemElement.h>
#include <feamy/models/shapefunctions/Tri6ShapeFunctions.h>

class Tri6Element : public FemElement{
public:
    Tri6Element(Conditions conditions, Triangle t, UniqueList<Point>& points, DOFS& out);
};

#endif