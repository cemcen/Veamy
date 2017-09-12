#ifndef VEAMY_FEMELEMENT_H
#define VEAMY_FEMELEMENT_H

#include <delynoi/models/polygon/Triangle.h>
#include <veamy/physics/VeamyConditions.h>
#include "veamy/models/Element.h"
#include "feamy/models/shapefunctions/ShapeFunctions.h"
#include <vector>

class FemElement: public Element<Triangle> {
private:
    ShapeFunctions N;
public:
    FemElement(VeamyConditions &conditions, Triangle &p, UniqueList<Point> &points, DOFS &out);
    void computeK(DOFS d, UniqueList<Point> points, VeamyConditions &conditions)=0;
    void computeF(DOFS d, UniqueList<Point> points, Conditions* conditions);
};

#endif