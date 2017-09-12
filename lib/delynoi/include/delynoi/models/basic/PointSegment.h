#ifndef DELYNOI_POINTSEGMENT_H
#define DELYNOI_POINTSEGMENT_H

#include <delynoi/models/basic/Point.h>
#include <delynoi/models/basic/Segment.h>

class PointSegment: public Segment<Point>{
public:
    PointSegment(Point p1, Point p2);
    PointSegment();

    bool contains(Point point);
    std::string getString() const override;
    bool operator==(const PointSegment other) const;
    bool intersectionInfinite(Point p1, Point p2, Point& inter);
};


#endif 
