#ifndef DELYNOI_DELYNOIUTILITIES_H
#define DELYNOI_DELYNOIUTILITIES_H

#include <vector>
#include <iostream>
#include <delynoi/models/basic/Point.h>
#include <utilities/Pair.h>

/*
 * Namespace that includes common geometric utilities of the Delynoi library
 */
namespace delynoi_utilities {
    /*
     * Returns the trivial vector of indexes of length n (0,1,2...,n-1)
     * @param index_vector vector that will be set with the trivial vector
     * @param n length of the generated vector
     */
    extern void TrivialIndexVector(std::vector<int>& index_vector, int n);

    /* Computes the cross product of two points
     * @param a b points to operate
     * @return result of the operation
     */
    extern double crossProduct(Point a, Point b);

    /* Computes the norm of a point (basically, a vector starting from the origin)
     * @param p point which norm will be calculated
     * @return norm of the point
     */
    extern double norm(Point p);

    /*Computes the square of the norm of a point (basically, a vector starting from the origin)
     * @param p point which square norm will be calculated
     * @return norm of the point
     */
    extern double squareNorm(Point p);

    /* Determines the orientation of three points (counter clockwise or clockwise)
     * @param p q r points to operate
     * @return whether the points are oriented counter clockwise (positive) or clockwise (negative)
     */
    extern double orientation(Point p, Point q, Point r);

    /* Creates a number of points that discretize a circle arc
     * @param center center of the circle
     * @param radius radius of the circle
     * @param initAngle initial angle of the curve
     * @param endAngle final angle of the curve
     * @return vector with the points representing the curve
     */
    extern std::vector<Point> generateArcPoints(Point center, double radius, double initAngle, double endAngle);
}
#endif