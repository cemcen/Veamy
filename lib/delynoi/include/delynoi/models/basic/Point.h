#ifndef DELYNOI_POINT_H
#define DELYNOI_POINT_H

#include <string>
#include <math.h>
#include <cmath>
#include <sstream>
#include <utilities/utilities.h>

/*
 * Models a geometrical two dimensional point.
 */
class Point {
private:
    /*
     * Values of the points x and y coordinates.
     */
    double x;
    double y;

    /*
     * Boolean flag indicating if the point is in the boundary of the mesh
     */
    bool isBoundaryPoint = false;

    /*
     * Boolean flag indicating if this point has been initialized
     */
    bool isEmpty = false;
public:
    /*
     * Constructor. Creates a point with its two coordinates.
     */
    Point(double x, double y);

    /*
     * Default constructor. Creates a point in the origin (0,0)
     */
    Point();

    /*
     * @return boolean indicating if this point is valid
     */
    bool isValid();

    /*
     * @return value of the x-axis of the point
     */
    double getX() const;

    /*
     * @return value of the y-axis of the point
     */
    double getY() const;

    /*
     * @return the square of the norm of the point
     */
    double squareNorm();

    /*
     * Returns the string representation of the point.
     * @return string representing the point as a pair of double numbers
     */
    std::string getString() const;

    /* Equality operator.
     * @param other point to compare
     * @return are the two points equal or not
     */
    bool operator==(const Point &other) const;

    /* Lesser than operator.
     * @param other point to compare against
     * @return is this point lesser that the other one
     */
    bool operator<(const Point& other) const;

    /* Substraction operator.
     * @param other point to operate with
     * @return the difference between the two points
     */
    Point operator-(const Point& other);

    /*
     * @return flag indicating if the point is in the boundary of the mesh
     */
    bool isInBoundary();

    /*
     * Sets the point as being in the boundary
     */
    void setBoundary();

    /* Changes the x-axis value of the point
     * @param newX new x value
     */
    void setX(double newX);

    /* Changes the y-axis value of the point
     * @param newY new y value
     */
    void setY(double newY);
};

#endif