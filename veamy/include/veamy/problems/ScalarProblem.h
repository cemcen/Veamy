#ifndef VEAMY_SCALARPROBLEM_H
#define VEAMY_SCALARPROBLEM_H

#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/models/constraints/EssentialConstraints.h>

class ScalarProblem {
public:
    void addConstraint(NaturalConstraints natural, PointConstraint constraint);
    void addConstraint(NaturalConstraints natural, SegmentConstraint constraint, const std::vector<Point> &points);
    void addConstraint(EssentialConstraints essential, PointConstraint constraint);
    void addConstraint(EssentialConstraints essential, SegmentConstraint constraint, const std::vector<Point> &points);
};

#endif