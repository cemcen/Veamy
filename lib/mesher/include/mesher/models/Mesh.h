#ifndef MESHER_MESH_H
#define MESHER_MESH_H

#include <mesher/models/neighbourhood/SegmentMap.h>
#include <utilities/UniqueList.h>
#include <fstream>

class Mesh{
protected:
    SegmentMap edges;
    UniqueList<Point> points;
public:
    void printInStream(std::ofstream& file);
    void printInFile(std::string fileName);
    virtual void writeElements(std::ofstream& file) = 0;

    SegmentMap& getSegments();
    SegmentMap getSegments() const ;

    UniqueList<Point>& getPoints();
    UniqueList<Point> getPoints() const;

    bool isFull();

    Point getPoint(int i);
    IndexSegment convertSegment(PointSegment s);
    Neighbours getNeighbours(IndexSegment s);
};


#endif