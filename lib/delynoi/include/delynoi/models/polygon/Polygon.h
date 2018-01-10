#ifndef DELYNOI_POLYGON_H
#define DELYNOI_POLYGON_H

#include <vector>
#include <delynoi/models/basic/Point.h>
#include <delynoi/models/basic/Segment.h>
#include <delynoi/utilities/geometryFunctions.h>
#include <delynoi/utilities/convexHull.h>
#include <delynoi/models/basic/IndexSegment.h>
#include <utilities/Pair.h>
#include <map>
#include <utilities/UniqueList.h>
#include <algorithm>
#include <delynoi/models/neighbourhood/SegmentMap.h>
#include <climits>

/*
 * Models a polygon (with an arbitrary number of sides)
 */
class Polygon {
protected:
    /*
     * List of the indexes (in the mesh) of the polygon points
     */
    std::vector<int> points;

    /*
     * Pre-calculated polygon properties
     */
    double diameter;
    double area;
    Point centroid;

    /* Calculates the polygon diameter
     * @param p mesh points
     * @return polygon diameter
     */
    double calculateDiameter(std::vector<Point> &p);

    /* Calculates the polygon area
     * @param p mesh points
     * @return polygon area
     */
    double calculateArea(std::vector<Point> &p);

    /* Calculates the polygon centroid
     * @param p mesh points
     * @return polygon centroid
     */
    Point calculateCentroid(std::vector<Point> &p);

    /*
     * Calculates the polygon hash value
     */
    void calculateHash();

public:
    /*
     * Constructor. Receives a list of point indexes and the mesh points to create the polygon
     */
    Polygon(std::vector<int> &points, std::vector<Point> &p);

    /*
     * Constructor. Receives a list of points representing the polygon
     */
    Polygon(std::vector<Point> &p);

    /*
     * Copy constructor.
     */
    Polygon(const Polygon &obj);

    /*
     * Default constructor.
     */
    Polygon();

    /*
     * @return polygon diameter
     */
    double getDiameter();

    /*
     * @return polygon area
     */
    double getArea();

    /*
     * @return polygon centroid
     */
    Point getCentroid();

    /* Gets the polygon segments and set them in the given vector
     * @param segments vector that will contain the segments
     */
    void getSegments(std::vector<IndexSegment> &segments);

    /*
     * @return polygon points indexes list
     */
    std::vector<int> getPoints() const;

    /*
     * @return reference to the polygon points indexes list
     */
    std::vector<int> &getPoints();

    /*
     * @param p mesh points
     * @return polygon point list (Point instances, not their indexes)
     */
    std::vector<Point> getPoints(std::vector<Point> p);

    /*
     * @return number of sides of the polygon
     */
    int numberOfSides() const;

    /*
     * Equality operator
     * @param other polygon to compare against
     * @return whether the two polygons are equal or not
     */
    bool operator==(const Polygon &other) const;

    /*
     * Less than operator.
     * @param other polygon to compare against
     * @return whether this polygon is less than the other
     */
    bool operator<(const Polygon &other) const;

    /* Gives a string representation of the polygon, first including the number of sides, followed by the indexes of
     * each point index
     * @return the string representation of the polygon
     */
    std::string getString();

    /* Changes the points defining the polygon, changing the value of the object without destroying this instance
     * @param p points to assign to this polygon
     */
    void mutate(std::vector<Point> &p);

    /* Determines if a point is inside the polygon
     * @param p mesh points
     * @param point point to check
     * @return whether the point is inside the polygon or not
     */
    bool containsPoint(std::vector<Point> &p, Point point);

    /* Determines if a point is in the border of the polygon
     * @param p mesh points
     * @param point point to check
     * @return whether the point is in the border of the polygon or not
     */
    bool inEdges(std::vector<Point> &p, Point point);

    /* Calculates the signed area of the polygon (using the counter-clockwise rule)
     * @param p mesh points
     * @return signed polygon area
     */
    double signedArea(std::vector<Point> &p);

    /* Checks if a segment is part of the polygon
     * @param s segment to check
     * @return if the segment is part of the polygon
     */
    bool containsEdge(IndexSegment s);

    /* Checks if the polygon is convex
     * @param p mesh points
     * @return if the polygon is convex or not
     */
    bool isConvex(std::vector<Point> &p);

    /* Checks if the polygon points are counter or clockwise checking the signed area of the points
     * @param p mesh points
     * @return if the points are ordered clockwise or not
     */
    bool isClockwise(std::vector<Point> &p);

    /* Checks if a given point index is part of the polygon (is a vertex)
     * @param index point index to check
     * @return if the index is a vertex or not
     */
    bool isVertex(int index);

    /* Checks if the polygon self-intersects
     * @param points mesh points
     * @return if the polygon is self-intersecting
     */
    bool isSelfIntersecting(std::vector<Point> &points);

    /*
     * Hash value of the polygon (calculated using the indexes of the points)
     */
    std::size_t hash;

    /* Checks if the polygon is in counter-clockwise or clockwise, and fixes the order of the point if the second is the
     * case.
     * @param p mesh points
     */
    void fixCCW(std::vector<Point> p);

    /* Finds the segment of the polygon that contains a given point
     * @param p mesh points
     * @param point point to use
     * @return segment that contains point
     */
    IndexSegment containerEdge(std::vector<Point>& p, Point point);

    /* Gets the average vertex value of the polygon
     * @param p mesh points
     * @return average point
     */
    Point getAverage(std::vector<Point> p);

    /*
     *
     */
    double getMaxDistance(std::vector<Point>& points);
};

#endif