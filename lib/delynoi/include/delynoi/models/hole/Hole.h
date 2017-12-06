#ifndef DELYNOI_HOLE_H
#define DELYNOI_HOLE_H

#include <delynoi/models/basic/Point.h>
#include <delynoi/models/basic/Segment.h>
#include <vector>
#include <delynoi/models/basic/IndexSegment.h>

class Hole {
protected:
    std::vector<Point> HolePoints;
    Point center;
    std::vector<IndexSegment> segments;
public:
    Hole(){};

    Hole(std::vector<Point> points, Point center, std::vector<IndexSegment> seg){
        this->center = center;
        this->HolePoints.assign(points.begin(), points.end());
        this->segments.assign(seg.begin(), seg.end());
    }

    Hole(const Hole& other){
        this->center = other.center;
        this->HolePoints.assign(other.HolePoints.begin(), other.HolePoints.end());
        this->segments.assign(other.segments.begin(), other.segments.end());
    }

    virtual Point getCenter(){
        return this->center;
    };

    void getSegments(std::vector<IndexSegment>& s, int offset){
        for (IndexSegment seg: this->segments) {
            s.push_back(seg.add(offset));
        }
    };

    virtual std::vector<Point> getPoints(){
        return this->HolePoints;
    };
};

#endif