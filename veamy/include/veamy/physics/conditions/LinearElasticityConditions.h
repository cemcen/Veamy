#ifndef VEAMY_LINEARELASTICITYCONDITIONS_H
#define VEAMY_LINEARELASTICITYCONDITIONS_H

#include <veamy/problems/elasticity/elasticity_constraints.h>
#include "Conditions.h"

/*
 * Class that contains the conditions unique to a linear elasticity problem (material matrix)
 */
class LinearElasticityConditions : public Conditions{
public:
    /*
     * Material properties of the domain
     */
    Material* material;

    /*
     * Constructor
     */
    LinearElasticityConditions(ConstraintsContainer container, BodyForce* f, Material* mat);

    /*
     * Constructor. As a body force is not given, the default value is used
     */
    LinearElasticityConditions(ConstraintsContainer container, Material* mat);

    /*
     * Constructor. Uses an empty constraint container
     */
    LinearElasticityConditions(Material* mat, BodyForce* force);

    /*
     * Constructor. Uses an empty constraint container and the default body force
     */
    LinearElasticityConditions(Material* mat);

    /* Adds a point constraint to the natural conditions
     * @param constraint condition to add
     * @param direction direction of the constraint
     */
    void addNaturalConstraint(PointConstraint& constraint, elasticity_constraints::Direction direction);

    /* Adds a segment constraint to the natural conditions
     * @param constraint condition to add
     * @param points mesh points
     * @param direction direction of the constraint
     */
    void addNaturalConstraint(SegmentConstraint &constraint, std::vector<Point> &points,
                              elasticity_constraints::Direction direction);

    /* Adds a segment constraint to the natural conditions
     * @param constraint condition to add
     * @param points mesh points
     * @param direction direction of the constraint
     */
    void addNaturalConstraint(SegmentConstraint &constraint, UniqueList<Point> &points,
                              elasticity_constraints::Direction direction);

    /* Adds a point constraint to the essential conditions
     * @param constraint condition to add
     * @param direction direction of the constraint
     */
    void addEssentialConstraint(PointConstraint& constraint, elasticity_constraints::Direction direction);

    /* Adds a segment constraint to the essential conditions
     * @param constraint condition to add
     * @param points mesh points
     * @param direction direction of the constraint
     */
    void addEssentialConstraint(SegmentConstraint& constraint, std::vector<Point>& points,
                                elasticity_constraints::Direction direction);

    /* Adds a segment constraint to the essential conditions
     * @param constraint condition to add
     * @param points mesh points
     * @param direction direction of the constraint
     */
    void addEssentialConstraint(SegmentConstraint& constraint, UniqueList<Point>& points,
                                elasticity_constraints::Direction direction);
};

#endif