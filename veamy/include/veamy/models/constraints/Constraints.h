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
#include <map>
#include "SegmentConstraint.h"
#include "PointConstraint.h"
#include <delynoi/models/basic/IndexSegment.h>
#include <delynoi/models/basic/Angle.h>

/*
 * Models the set of points and segments under constraints
 */
class Constraints {
protected:
    /*
     * Map relating angle of the constrained segments and the segments themselves, making searches more efficient
     */
    std::map<Angle, std::vector<IndexSegment>> constrained_segments;

    /*
     * Map that relates segments and their SegmentConstraints
     */
    std::unordered_map<IndexSegment, std::vector<SegmentConstraint>, SegmentHasher> segment_map;

    /*
     * Map relating DOF index with SegmentConstraints
     */
    std::unordered_map<int, SegmentConstraint, intHasher> segment_constraints_map;

    /*
     * Map relating Point and their PointConstraints
     */
    std::map<Point, std::vector<PointConstraint>> point_map;

    /*
     * Map relating DOF index and PointConstraint
     */
    std::unordered_map<int, PointConstraint, intHasher> point_constraints_map;

    /*
     * List of the indexes of all constrained DOFs
     */
    UniqueList<int> constrained_dofs;

    /* Checks if a DOF has a related SegmentConstraint and fills the maps appropriately
     * @param segment segment containing the DOF
     * @param DOF_index index of the DOF
     * @param axis axis of the DOF
     * @return if the DOF was constrained or not
     */
    bool constrainDOFBySegment(IndexSegment segment, int DOF_index, DOF::Axis axis);

    /* Checks if a DOF has a related SegmentConstraint and fills the maps appropriately
     * @param segment segment containing the DOF
     * @param DOF_index index of the DOF
     * @return if the DOF was constrained or not
     */
    bool constrainDOFBySegment(IndexSegment segment, int DOF_index);
public:
    /* Adds a new SegmentConstraint to this Constraints
     * @param c new SegmentConstraint
     * @param p list of mesh points
     */
    void addConstraint(SegmentConstraint c, std::vector<Point> p);

    /* Adds a new SegmentConstraint to this Constraints
     * @param c new SegmentConstraint
     * @param p unique list of mesh points
     */
    void addConstraint(SegmentConstraint c, UniqueList<Point> p);

    /* Adds a new PointConstraint to this Constraints
     * @param new PointConstraint
     */
    void addConstraint(PointConstraint c);

    /* Checks if a segment is constrained
     * @param points mesh points
     * @param p segment to check
     * @return is p constrained or not
     */
    isConstrainedInfo isConstrainedBySegment(std::vector<Point> points, IndexSegment p);

    /* Checks if a point is constrained
     * @param p point to check
     * @return is p constrained or not
     */
    isConstrainedInfo isConstrainedByPoint(Point p);

    /* Checks if a DOF is constrained or not
     * @param dof index of the DOF
     * @return if the DOF is constrained or not
     */
    bool isConstrained(int dof);

    /*
     * @return list of the indexes of all constrained DOFs
     */
    std::vector<int> getConstrainedDOF();

    /* Adds a DOF and checks if it is constrained, filling map information as necessary
     * @param points mesh points
     * @param DOF_index index of the DOF to add
     * @param axis axis of the DOF
     * @param pair pair of segments containing the DOF
     * @param dof_point index of the points associated to the DOF
     */
    void addConstrainedDOF(std::vector<Point> points, int DOF_index, DOF::Axis axis, SegmentPair pair,
                           int dof_point);

    /* Adds a DOF and checks if it is constrained, filling map information as necessary
     * @param points mesh points
     * @param DOF_index index of the DOF to add
     * @param pair pair of segments containing the DOF
     * @param dof_point index of the points associated to the DOF
     */
    void addConstrainedDOF(std::vector<Point> points, int DOF_index, SegmentPair pair, int dof_point);

    /* Adds a new DOF, checking if it is constrained due to SegmentConstraints
     * @param points mesh points
     * @param DOF_index index of the DOF
     * @param axis axis of the DOF
     * @param s segment containing the DOF
     * @return if the DOF is constrained
     */
    bool addConstrainedDOFBySegment(std::vector<Point> points, int DOF_index, DOF::Axis axis, IndexSegment s);

    /* Adds a new DOF, checking if it is constrained due to SegmentConstraints
     * @param points mesh points
     * @param DOF_index index of the DOF
     * @param s segment containing the DOF
     * @return if the DOF is constrained
     */
    bool addConstrainedDOFBySegment(std::vector<Point> points, int DOF_index, IndexSegment s);

    /* Adds a new DOF, checking if it is constrained due to PointConstraints
     * @param DOF_index index of the DOF
     * @param axis axis of the DOF
     * @param s point related to the DOF
     * @return if the DOF is constrained
     */
    bool addConstrainedDOFByPoint(int DOF_index, DOF::Axis axis, Point p);

    /* Adds a new DOF, checking if it is constrained due to PointConstraints
     * @param DOF_index index of the DOF
     * @param s point related to the DOF
     * @return if the DOF is constrained
     */
    bool addConstrainedDOFByPoint(int DOF_index, Point p);

    /* Checks if a point is contained in a constrained segment
     * @param p point to check
     * @param points mesh points
     * @param DOF_index index of the DOF
     * @param axis axis of the DOF
     * @return if the DOF is constrained
     */
    bool checkIfContainedInConstraint(Point p, std::vector<Point> points, int DOF_index, DOF::Axis axis);

    /* Checks if a point is contained in a constrained segment
     * @param p point to check
     * @param points mesh points
     * @param DOF_index index of the DOF
     * @return if the DOF is constrained
     */
    bool checkIfContainedInConstraint(Point p, std::vector<Point> points, int DOF_index);

    /*
     * @return the map with the constrained segments
     */
    std::unordered_map<IndexSegment, std::vector<SegmentConstraint>, SegmentHasher> getConstrainedSegments();

    /* Finds the associated Constraint to a given DOF
     * @param dof_index index of the DOF to lookup
     * @return the Constraint associated to the DOF
     */
    Constraint getAssociatedConstraint(int dof_index);
};


#endif
