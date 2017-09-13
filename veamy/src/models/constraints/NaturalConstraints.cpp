#include <veamy/models/constraints/NaturalConstraints.h>

NaturalConstraints::NaturalConstraints() {}

std::vector<SegmentConstraint> NaturalConstraints::getConstraintInformation(IndexSegment segment) {
    return segment_map[segment];
}

std::vector<PointConstraint> NaturalConstraints::getConstraintInformation(Point point) {
    return point_map[point];
}
