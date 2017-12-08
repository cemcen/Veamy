#ifndef DELYNOI_HOLE_H
#define DELYNOI_HOLE_H

#include <delynoi/models/basic/Point.h>
#include <delynoi/models/basic/Segment.h>
#include <vector>
#include <delynoi/models/basic/IndexSegment.h>

/*
 * Class that models a generic hole, which has a center and a list of points that define its boundary.
 */
class Hole {
protected:
    /*
     * Elements that define the hole, its points, center and segments.
     */
    std::vector<Point> HolePoints;
    Point center;
    std::vector<IndexSegment> segments;
public:
    /*
     * Default constructor.
     */
    Hole(){};

    /*
     * Constructor.
     */
    Hole(std::vector<Point> points, Point center, std::vector<IndexSegment> seg){
        this->center = center;
        this->HolePoints.assign(points.begin(), points.end());
        this->segments.assign(seg.begin(), seg.end());
    }

    /*
     * Copy constructor.
     */
    Hole(const Hole& other){
        this->center = other.center;
        this->HolePoints.assign(other.HolePoints.begin(), other.HolePoints.end());
        this->segments.assign(other.segments.begin(), other.segments.end());
    }

    /*
     * @return the center of the hole
     */
    virtual Point getCenter(){
        return this->center;
    };


    /*
     * @param s vector in which the hole segments will be set
     * @param offset value to add to the segment (representing that the hole could belong in a mesh with many points)
     */
    void getSegments(std::vector<IndexSegment>& s, int offset){
        for (IndexSegment seg: this->segments) {
            s.push_back(seg.add(offset));
        }
    };

    /*
     * @return list of points defining the hole
     */
    virtual std::vector<Point> getPoints(){
        return this->HolePoints;
    };
};

#endif