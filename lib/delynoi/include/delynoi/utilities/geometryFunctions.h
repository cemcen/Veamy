#ifndef DELYNOI_GEOMETRYFUNCTIONS_H
#define DELYNOI_GEOMETRYFUNCTIONS_H

#include <delynoi/models/basic/Point.h>
#include <delynoi/models/basic/PointSegment.h>
#include <vector>

/*
 * Namespace that contains all standard geometric functions
 */
namespace geometry_functions{
    /* Calculates the area2 defined by three points
     * @param p1 p2 p3 points that define the area
     * @return the value of the area2
     */
    extern double area2(Point p1, Point p2, Point p3);

    /* Determines if three points are collinear
     * @param p1 p2 p3 points to test
     * @return are the points collinear or not
     */
    extern bool collinear(Point p1, Point p2, Point p3);

    /* Determmines if two line segments are collinear
     * @param seg1 seg2 segments to test
     * @return are the segments collinear or not
     */
    extern bool collinear(PointSegment& seg1, PointSegment& seg2);

    /* Calculates the area of a triangle defined by three points
     * @param p1 p2 origin points that define an area
     * @return area of the triangle
     */
    extern double triangleArea(Point p1, Point p2, Point origin);

    /* Computes the area of a polygon defined by a set of point indexes
     * @param points points with the indexes reference
     * @param index indexes of the points defining the polygon
     * @return area of the polygon
     */
    extern double area(std::vector<Point>& points, std::vector<int> index);

    /* Computes the area of a polygon defined by a set of points
     * @param points points that define the polygon
     * @return area of the polygon
     */
    extern double area(std::vector<Point>& points);
}

#endif
