#ifndef DELYNOI_RECTANGLE_H
#define DELYNOI_RECTANGLE_H

#include <delynoi/models/basic/Point.h>
#include <delynoi/models/basic/PointSegment.h>

/*
 * Models an axes oriented bounding box (basically, a rectangle)
 */
class BoundingBox {
private:
    /*
     * Corners of the rectangle
     */
    Point p1;
    Point p2;

public:
    /*
     * Constructor
     */
    BoundingBox(Point p1, Point p2);

    /*
     * @return the first corner of the bounding box
     */
    Point getFirst() const;

    /*
     * @return the second corner of the bounding box
     */
    Point getSecond() const;

    /*
     * @return width of the box
     */
    double getWidth();

    /*
     * @return height of the box
     */
    double getHeight();

    /*
     * @return x-axis value of the left side of the box
     */
    double xMin();

    /*
     * @return y-axis value of the bottom side of the box
     */
    double yMin();

    /*
     * @return x-axis value of the right side of the box
     */
    double xMax();

    /*
     * @return y-axis value of the top side of the box
     */
    double yMax();

    /* Equality operator
     * @param
     * @return
     */
    bool operator==(const BoundingBox& other) const;

    /* Checks if a point is inside the box
     * @param p point to check
     * @return whether the point is inside the box or not
     */
    bool contains(Point p);

    /* Fills a vector with the segments of the box
     * @param segments vector in which the segments of the box will be kept
     */
    void getSegments(std::vector<PointSegment>& segments);
};


#endif
