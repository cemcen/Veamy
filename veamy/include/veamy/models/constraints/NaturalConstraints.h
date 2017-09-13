#ifndef VEAMY_NATURALCONSTRAINTS_H
#define VEAMY_NATURALCONSTRAINTS_H

#include <delynoi/models/polygon/Polygon.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/constraints/Constraints.h>

class NaturalConstraints : public Constraints{
public:
    NaturalConstraints();
    std::vector<SegmentConstraint> getConstraintInformation(IndexSegment segment);
    std::vector<PointConstraint> getConstraintInformation(Point point);
};


#endif
