#ifndef VEAMY_CONSTRAINTS_H
#define VEAMY_CONSTRAINTS_H

#include <delynoi/models/basic/Segment.h>
#include <veamy/models/dof/DOF.h>
#include <veamy/utilities/SegmentPair.h>
#include <utilities/UniqueList.h>
#include <veamy/models/constraints/Constraint.h>
#include <veamy/models/constraints/structures/constrained_seg_mapdata.h>
#include <delynoi/models/neighbourhood/PointMap.h>
#include <veamy/models/constraints/structures/isConstrainedInfo.h>
#include <delynoi/voronoi/structures/mapdata.h>
#include <veamy/models/constraints/structures/Angle.h>
#include <map>
#include "SegmentConstraint.h"
#include "PointConstraint.h"

class Constraints {
protected:
    std::map<Angle, std::vector<IndexSegment>> constrained_segments;

    std::unordered_map<IndexSegment, std::vector<SegmentConstraint>, SegmentHasher> segment_map;
    std::unordered_map<int, SegmentConstraint, intHasher> segment_constraints_map;
    std::unordered_map<Point, std::vector<PointConstraint>, PointHasher> point_map;
    std::unordered_map<int, PointConstraint, intHasher> point_constraints_map;
    UniqueList<int> constrained_dofs;
public:
    void addConstraint(SegmentConstraint c, std::vector<Point> p);
    void addConstraint(SegmentConstraint c, UniqueList<Point> p);
    void addConstraint(PointConstraint c);

    isConstrainedInfo isConstrainedBySegment(std::vector<Point> points, IndexSegment p);
    isConstrainedInfo isConstrainedByPoint(Point p);
    bool isConstrained(int dof);

    std::vector<int> getConstrainedDOF();
    void addConstrainedDOF(std::vector<Point> points, int DOF_index, DOF::Axis axis, SegmentPair pair,
                           int dof_point);
    bool addConstrainedDOFBySegment(std::vector<Point> points, int DOF_index, DOF::Axis axis, IndexSegment s);
    bool addConstrainedDOFByPoint(int DOF_index, DOF::Axis axis, Point p);
    std::unordered_map<IndexSegment, std::vector<SegmentConstraint>, SegmentHasher> getConstrainedSegments();
    Constraint getAssociatedConstraint(int dof_index);
};


#endif
