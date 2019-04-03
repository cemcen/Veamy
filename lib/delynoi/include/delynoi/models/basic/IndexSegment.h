#ifndef DELYNOI_INDEXSEGMENT_H
#define DELYNOI_INDEXSEGMENT_H

#include <delynoi/models/basic/Segment.h>
#include <delynoi/models/basic/PointSegment.h>

/*
 * This class models a segment which endpoints are represented by their indexes in the mesh.
 */
class IndexSegment: public Segment<int>{
public:
    /*
     *
     */
    std::size_t hash = 0;

    /*
     * Constructor. Creates an empty segment.
     */
    IndexSegment();

    /*
     * Constructor. Creates a segment with assigned endpoints.
     */
    IndexSegment(int i1, int i2);

    /*
     * Copy constructor.
     */
    IndexSegment(const IndexSegment& other);

    /*
     * Determines if a point is contained in the segment.
     * @param p mesh points
     * @param point to check
     * @return if the point is contained or not
     */
    bool contains(const std::vector<Point>& p, Point point);

    /*
     * Determines if a point is contained in the segment.
     * @param p mesh points
     * @param point to check
     * @return if the point is contained or not
     */
    bool contains(const std::vector<Point>& p, IndexSegment s);

    /*
     * @param p mesh points
     * @return point in the middle of the segment
     */
    Point middlePoint(const std::vector<Point>& p);

    /*
     * @param p mesh points
     * @return angle of the segment in degrees
     */
    double cartesianAngle(const std::vector<Point>& p);

    /*  Determines whether two segments intersect or not. Sets the intersection point in the last argument.
     * @param p mesh points
     * @param other second segment
     * @param inter intersection point (only valid if segments intersect)
     * @return segments intersect or not
     */
    bool intersection(const std::vector<Point>& points, PointSegment other, Point &inter);

    /*  Determines whether two segments intersect or not. Sets the intersection point in the last argument.
     * @param p mesh points
     * @param other second segment
     * @param inter intersection point (only valid if segments intersect)
     * @return segments intersect or not
     */
    bool intersection(const std::vector<Point>& points, IndexSegment other, Point &inter);

    /*  Determines a segment is contained in this one.
     * @param s segment to check
     * @param p mesh points
     * @return segment is contained or not
     */
    bool isContained(PointSegment s, const std::vector<Point>& p);

    /* Orders the segment in counter-clockwise order with respect a reference point.
     * @param points mesh points
     * @param reference point
     */
    void orderCCW(const std::vector<Point>& points, Point center);

    /*
     * @param points mesh points
     * @param center reference point
     * @return is the segment ordered in counter-clockwise order
     */
    bool isCCW(const std::vector<Point>& points, Point center);

    /*
     * Returns the string representation of the segment.
     * @return string representing the segment as a pair
     */
    std::string getString() const override;

    /* Equality operator.
     * @param other segment to compare
     * @return are the two segments equal or not
     */
    bool operator==(const IndexSegment& other) const;

    /* Lesser than operator.
     * @param other segment to compare against
     * @return is this segment lesser that the other one
     */
    bool operator<(const IndexSegment& other) const;

    /*
     * @param points mesh points
     * @return length of the segment
     */
    double length(const std::vector<Point>& points);

    /* Displaces the segment.
     * @param o value of the segment displacement
     */
    IndexSegment add(int o);
};


#endif 
