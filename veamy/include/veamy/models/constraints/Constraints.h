#ifndef VEAMY_CONSTRAINTS_H
#define VEAMY_CONSTRAINTS_H

#include <mesher/models/basic/Segment.h>
#include <veamy/models/dof/DOF.h>
#include <veamy/utilities/SegmentPair.h>
#include <utilities/UniqueList.h>
#include <veamy/models/constraints/Constraint.h>
#include <veamy/models/constraints/structures/constrained_seg_mapdata.h>
#include <veamy/models/constraints/structures/isConstrainedInfo.h>
#include <mesher/voronoi/structures/mapdata.h>
#include <veamy/models/constraints/structures/Angle.h>
#include <map>

class Constraints {
protected:
    std::map<Angle, std::vector<IndexSegment>> constrained_segments;

    std::unordered_map<IndexSegment, Constraint, SegmentHasher> segment_map;
    std::unordered_map<int, Constraint, intHasher> constraints_map;
    UniqueList<int> constrained_dofs;
public:
    void addConstraint(Constraint c, std::vector<Point> p);
    isConstrainedInfo isConstrained(std::vector<Point> points, IndexSegment p);
    bool isConstrained(int dof);

    std::vector<int> getConstrainedDOF();
    void addConstrainedDOF(std::vector<Point> points, int DOF_index, DOF::Axis axis, SegmentPair pair);
    void addConstrainedDOFBySegment(std::vector<Point> points, int DOF_index, DOF::Axis axis, IndexSegment s);
    std::unordered_map<IndexSegment, Constraint, SegmentHasher> getConstrainedSegments();
};


#endif
