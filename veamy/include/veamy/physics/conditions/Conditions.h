#ifndef VEAMY_CONDITIONS_H
#define VEAMY_CONDITIONS_H

#include <veamy/physics/bodyforces/BodyForce.h>
#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/physics/materials/Material.h>
#include <veamy/physics/bodyforces/None.h>


class Conditions{
public:
    /*
     * Conditions of the problem
     */
    ConstraintsContainer constraints;
    BodyForce* f;

    /*
     * Constructor
     */
    Conditions(ConstraintsContainer container, BodyForce* bodyForce);

    /*
     * Constructor, begins with an empty constraints container that can be later assigned
     */
    Conditions(BodyForce* bodyForce);

    /*
     * Default constructor
     */
    Conditions();

    /* Adds a point constraint to the natural conditions
     * @param constraint condition to add
     */
    void addNaturalConstraint(PointConstraint& constraint);

    /* Adds a segment constraint to the natural conditions
     * @param constraint condition to add
     * @param points mesh points
     */
    void addNaturalConstraint(SegmentConstraint &constraint, std::vector<Point> &points);

    /* Adds a segment constraint to the natural conditions
     * @param constraint condition to add
     * @param points mesh points
     */
    void addNaturalConstraint(SegmentConstraint &constraint, UniqueList<Point> &points);

    /* Adds a point constraint to the essential conditions
     * @param constraint condition to add
     */
    void addEssentialConstraint(PointConstraint& constraint);

    /* Adds a segment constraint to the essential conditions
     * @param constraint condition to add
     * @param points mesh points
     */
    void addEssentialConstraint(SegmentConstraint& constraint, std::vector<Point>& points);

    /* Adds a segment constraint to the essential conditions
     * @param constraint condition to add
     * @param points mesh points
     */
    void addEssentialConstraint(SegmentConstraint& constraint, UniqueList<Point>& points);

};


#endif