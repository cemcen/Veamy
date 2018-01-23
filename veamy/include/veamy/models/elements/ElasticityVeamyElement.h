#ifndef VEAMY_ELASTICITYVEAMYELEMENT_H
#define VEAMY_ELASTICITYVEAMYELEMENT_H

#include <veamy/physics/conditions/LinearElasticityConditions.h>
#include "VeamyElement.h"
#include <veamy/config/VeamyConfig.h>

/*
 * Models a VEM element solving a linear elasticity problem
 */
class ElasticityVeamyElement : public VeamyElement{
private:
    /*
     * Conditions of the linear elasticity problem
     */
    LinearElasticityConditions* conditions;
public:
    /*
     * Constructor
     */
    ElasticityVeamyElement(LinearElasticityConditions *conditions, Polygon &p, UniqueList<Point> &points,
                           DOFS &out,
                           int n_dofs);

    /* Computes the elemental stiffness matrix
     * @param d degrees of freedom of the system
     * @param points mesh points
     */
    void computeK(DOFS &d, UniqueList<Point> &points);
};

#endif