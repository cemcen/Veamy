#ifndef DELYNOI_GEOMETRYFUNCTIONS_H
#define DELYNOI_GEOMETRYFUNCTIONS_H

#include <delynoi/models/basic/Point.h>
#include <delynoi/models/basic/PointSegment.h>
#include <vector>

namespace geometry_functions{
    extern double area2(Point p1, Point p2, Point p3);
    extern bool collinear(Point p1, Point p2, Point p3);
    extern bool collinear(PointSegment seg1, PointSegment seg2);
    extern double triangleArea(Point p1, Point p2, Point origin);
    extern double area(std::vector<Point> points, std::vector<int> index);
    extern double area(std::vector<Point> points);
}

#endif
