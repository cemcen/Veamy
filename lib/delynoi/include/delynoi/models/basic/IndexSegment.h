#ifndef DELYNOI_INDEXSEGMENT_H
#define DELYNOI_INDEXSEGMENT_H

#include <delynoi/models/basic/Segment.h>
#include <delynoi/models/basic/PointSegment.h>


class IndexSegment: public Segment<int>{
public:
    IndexSegment();
    IndexSegment(int i1, int i2);
    IndexSegment(const IndexSegment& other);

    bool contains(std::vector<Point>& p, Point point);
    bool contains(std::vector<Point> p, IndexSegment s);
    Point middlePoint(std::vector<Point> p);
    double cartesianAngle(std::vector<Point> p);
    bool intersection(std::vector<Point> points, PointSegment other, Point &inter);
    bool intersection(std::vector<Point> points, IndexSegment other, Point &inter);
    bool isContained(PointSegment s, std::vector<Point> p);
    void orderCCW(std::vector<Point> points, Point center);
    bool isCCW(std::vector<Point> points, Point center);
    std::string getString() const override;
    bool operator==(const IndexSegment& other) const;
    bool operator<(const IndexSegment& other) const;
    bool isInCorner(Point p, std::vector<Point> points, int& i);
    double length(std::vector<Point>& points);
    IndexSegment add(int o);
};


#endif 
