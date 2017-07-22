#ifndef VEAMY_CONSTRAINT_H
#define VEAMY_CONSTRAINT_H

#include <mesher/models/basic/Point.h>
#include <vector>
#include <unordered_map>
#include <veamy/models/constraints/values/ConstraintValue.h>
#include <mesher/models/basic/IndexSegment.h>
#include <utilities/UniqueList.h>
#include <utilities/Pair.h>

class Constraint{
public:
    enum Direction {Vertical, Horizontal, Total};
private:
    UniqueList<IndexSegment> constraints;
    ConstraintValue* v;
    Direction direction;

    IndexSegment fromPointToInt(PointSegment s, std::vector<Point> points);
public:
    Constraint();
    Constraint(IndexSegment s, Direction d, ConstraintValue* value);
    Constraint(std::vector<IndexSegment> s, Direction d, ConstraintValue* value);

    Constraint(PointSegment s, std::vector<Point> points, Direction d, ConstraintValue* value);
    Constraint(PointSegment s, UniqueList<Point> points, Direction d, ConstraintValue* value);

    Constraint(std::vector<PointSegment> s, std::vector<Point> points, Direction d, ConstraintValue* value);
    Constraint(std::vector<PointSegment> s, UniqueList<Point> points, Direction d, ConstraintValue* value);

    double getValue(Point p);
    UniqueList<IndexSegment> getSegments();
    Direction getDirection();

    Pair<int> getIndex(int point_index);

};


#endif
