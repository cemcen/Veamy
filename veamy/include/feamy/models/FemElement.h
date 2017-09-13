#ifndef VEAMY_FEMELEMENT_H
#define VEAMY_FEMELEMENT_H

#include <delynoi/models/polygon/Triangle.h>
#include <veamy/physics/Conditions.h>
#include "veamy/models/Element.h"
#include "feamy/models/shapefunctions/ShapeFunctions.h"
#include <vector>

class FemElement: public Element<Triangle> {
protected:
    ShapeFunctions* N;
public:
    FemElement();
    void initializeElement(Conditions &conditions, Triangle &p, UniqueList<Point> &points, DOFS &out, ShapeFunctions* N);
    virtual void computeK(DOFS d, UniqueList<Point> points, Conditions &conditions) = 0;
    void computeF(DOFS d, UniqueList<Point> points, Conditions& conditions);
};

#endif