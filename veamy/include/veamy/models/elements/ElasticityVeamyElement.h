#ifndef VEAMY_ELASTICITYVEAMYELEMENT_H
#define VEAMY_ELASTICITYVEAMYELEMENT_H

#include <veamy/physics/conditions/LinearElasticityConditions.h>
#include "VeamyElement.h"
#include <veamy/config/VeamyConfig.h>

class ElasticityVeamyElement : public VeamyElement{
private:
    LinearElasticityConditions* conditions;
public:
    ElasticityVeamyElement(LinearElasticityConditions *conditions, Polygon &p, UniqueList<Point> &points,
                           DOFS &out,
                           int n_dofs);
    void computeK(DOFS &d, UniqueList<Point> &points);
};

#endif