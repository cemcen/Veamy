#ifndef DELYNOI_MESH_H
#define DELYNOI_MESH_H

#include <delynoi/models/neighbourhood/SegmentMap.h>
#include <utilities/UniqueList.h>
#include <fstream>
#include <delynoi/models/polygon/Polygon.h>
#include <delynoi/models/neighbourhood/PointMap.h>
#include <delynoi/models/polygon/Triangle.h>
#include <utilities/utilities.h>

template <typename T>
class Mesh{
protected:
    SegmentMap edges;
    PointMap pointMap;
    UniqueList<Point> points;
    std::vector<T> polygons;
public:
    Mesh();
    Mesh(std::vector<Point> &p, std::vector<T> &e, SegmentMap s, PointMap pM);
    Mesh(UniqueList<Point> p, std::vector<T>& e, SegmentMap s, PointMap pM);
    Mesh(const Mesh& m);
    void printInStream(std::ofstream& file);
    void printInFile(std::string fileName);
    void createFromFile(std::string fileName);
    void createFromStream(std::ifstream& ofstream);

    std::vector<T>& getPolygons();
    std::vector<T> getPolygons() const;
    T& getPolygon(int index);

    SegmentMap& getSegments();
    SegmentMap getSegments() const ;

    PointMap& getPointMap();
    PointMap getPointMap() const;

    UniqueList<Point>& getPoints();
    UniqueList<Point> getPoints() const;

    Point getPoint(int i);
    NeighboursBySegment getNeighbours(IndexSegment s);
};


#endif