#ifndef MESHER_HOLE_H
#define MESHER_HOLE_H

#include <mesher/models/basic/Point.h>
#include <mesher/models/basic/Segment.h>
#include <vector>
#include <mesher/models/basic/IndexSegment.h>

class Hole {
protected:
    std::vector<Point> HolePoints;
    Point center;
    std::vector<IndexSegment> segments;
public:
    Hole(){};
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