#ifndef VEAMY_NATURALCONSTRAINTS_H
#define VEAMY_NATURALCONSTRAINTS_H

#include <delynoi/models/polygon/Polygon.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/constraints/Constraints.h>

/*
 * Contains the natural (Neumann) boundary conditions
 */
class NaturalConstraints : public Constraints{
public:
    /*
     * Default constructor
     */
    NaturalConstraints();

    /* Returns all constraints related to a segment
     * @param segment segment to lookup
     * @return all SegmentConstraints related to the segment
     */
    std::vector<SegmentConstraint> getConstraintInformation(IndexSegment segment);

    /* Returns all constraints related to a point
     * @param point point to lookup
     * @return all PointConstraints related to the point
     */
    std::vector<PointConstraint> getConstraintInformation(Point point);
};


#endif
