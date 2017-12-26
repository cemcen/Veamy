#ifndef VEAMY_VECTORIALPROBLEM_H
#define VEAMY_VECTORIALPROBLEM_H

#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/models/constraints/EssentialConstraints.h>

class VectorialProblem {
public:
    void addConstraint(NaturalConstraints natural, PointConstraint constraint, Constraint::Direction d);
    void addConstraint(NaturalConstraints natural, SegmentConstraint constraint, Constraint::Direction d);
    void addConstraint(EssentialConstraints essential, PointConstraint constraint, Constraint::Direction d);
    void addConstraint(EssentialConstraints essential, SegmentConstraint constraint, Constraint::Direction d);
};

#endif