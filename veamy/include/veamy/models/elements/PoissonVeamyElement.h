#ifndef VEAMY_POISSONVEAMYELEMENT_H
#define VEAMY_POISSONVEAMYELEMENT_H

#include <veamy/physics/conditions/PoissonConditions.h>
#include "VeamyElement.h"

class PoissonVeamyElement : public VeamyElement{
protected:
    PoissonConditions* conditions;
public:
    PoissonVeamyElement(PoissonConditions *conditions, Polygon &p, UniqueList<Point> &points, DOFS &out, int n_dofs);
    void computeK(DOFS &d, UniqueList<Point> &points);
};

#endif