#ifndef DELYNOI_SEGMENT_H
#define DELYNOI_SEGMENT_H

#include <vector>
#include <delynoi/models/basic/Point.h>
#include <delynoi/utilities/xpolyutilities.h>
#include <delynoi/config/DelynoiConfig.h>

template <class T>
class Segment {
protected:
    T p1;
    T p2;

    bool intersects(Point p1, Point p2, Point o1, Point o2, Point& inter);
    bool intersectionInfinite(Point p1, Point p2, Point o1, Point o2, Point &inter);
    bool contains(Point point, Point p1, Point p2);
public:
    Segment();
    Segment(T p1, T p2);
    ~Segment();

    T getFirst() const;
    T getSecond() const;

    virtual std::string getString() const = 0;
    bool isVertex(T p);

};

#endif



