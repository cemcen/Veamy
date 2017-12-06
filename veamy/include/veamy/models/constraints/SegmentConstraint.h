#ifndef VEAMY_SEGMENTCONSTRAINT_H
#define VEAMY_SEGMENTCONSTRAINT_H

#include "Constraint.h"
#include <delynoi/models/basic/IndexSegment.h>

class SegmentConstraint: public Constraint{
private:
    UniqueList<IndexSegment> constraints;
    IndexSegment fromPointToInt(PointSegment s, std::vector<Point> points);
public:
    SegmentConstraint();
    SegmentConstraint(IndexSegment s, Constraint::Direction d, ConstraintValue *value);
    SegmentConstraint(std::vector<IndexSegment> s, Constraint::Direction d, ConstraintValue *value);
    SegmentConstraint(PointSegment s, std::vector<Point> points, Constraint::Direction d, ConstraintValue *value);
    SegmentConstraint(PointSegment s, UniqueList<Point> points, Constraint::Direction d, ConstraintValue *value);
    SegmentConstraint(std::vector<PointSegment> s, std::vector<Point> points, Constraint::Direction d,
                      ConstraintValue *value);
    SegmentConstraint(std::vector<PointSegment> s, UniqueList<Point> points, Constraint::Direction d,
                      ConstraintValue *value);

    UniqueList<IndexSegment> getSegments();

};

#endif