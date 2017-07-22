#ifndef MESHER_INDEXSEGMENT_H
#define MESHER_INDEXSEGMENT_H

#include <mesher/models/basic/Segment.h>
#include <mesher/models/basic/PointSegment.h>


class IndexSegment: public Segment<int>{
public:
    IndexSegment();
    IndexSegment(int i1, int i2);
    IndexSegment(const IndexSegment& other);
    ~IndexSegment();

    bool isBoundary(std::vector<Point> p);
    bool contains(std::vector<Point>& p, Point point);
    bool contains(std::vector<Point> p, IndexSegment s);
    Point middlePoint(std::vector<Point> p);
    double cartesianAngle(std::vector<Point> p);
    bool intersection(std::vector<Point> points, PointSegment other, Point &inter);
    bool intersection(std::vector<Point> points, IndexSegment other, Point &inter);
    bool isContained(PointSegment s, std::vector<Point> p);
    void orderCCW(std::vector<Point> points, Point center);
    bool isCCW(std::vector<Point> points, Point center);
    std::string getString() const;
    bool operator==(const IndexSegment& other) const;
    bool operator<(const IndexSegment& other) const;
    double length(std::vector<Point>& points);
    bool isInCorner(Point p, std::vector<Point> points, int& i);
    IndexSegment add(int o);
    bool isEndPoint(Point p, std::vector<Point> points);
    PointSegment toPointSegment(std::vector<Point> points);
};


#endif 
