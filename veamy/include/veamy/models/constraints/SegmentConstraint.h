#ifndef VEAMY_SEGMENTCONSTRAINT_H
#define VEAMY_SEGMENTCONSTRAINT_H

#include "Constraint.h"
#include <delynoi/models/basic/IndexSegment.h>

/*
 * Models a constraint applied on a set of segments
 */
class SegmentConstraint: public Constraint{
private:
    /*
     * Constrained segments
     */
    UniqueList<IndexSegment> constraints;

    /* Converts a PointSegment to a IndexSegment
     * @param s PointSegment to convert
     * @param points mesh points
     * @return IndexSegment version of s
     */
    IndexSegment fromPointToInt(const PointSegment& s, const std::vector<Point>& points);
public:
    /*
     * Default constructor
     */
    SegmentConstraint();

    /*
     * Constructor. Constraints one IndexSegment
     */
    SegmentConstraint(IndexSegment s, ConstraintValue *value);

    /*
     * Constructor. Constraints a set of IndexSegments
     */
    SegmentConstraint(std::vector<IndexSegment> s, ConstraintValue *value);

    /*
     * Constructor. Constraints a PointSegment (more intuitive to the user)
     */
    SegmentConstraint(PointSegment &s, std::vector<Point> &points, ConstraintValue *value);

    /*
     * Constructor. Constraints a PointSegment
     */
    SegmentConstraint(PointSegment &s, UniqueList<Point> &points, ConstraintValue *value);

    /*
     * Constructor. Constraints a set of PointSegments
     */
    SegmentConstraint(std::vector<PointSegment> &s, std::vector<Point> &points, ConstraintValue *value);

    /*
     * Constructor. Constraints a set of PointSegments
     */
    SegmentConstraint(std::vector<PointSegment> &s, UniqueList<Point> &points, ConstraintValue *value);

    /*
     * @return list of segments constrained
     */
    UniqueList<IndexSegment> getSegments();

};

#endif