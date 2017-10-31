#ifndef DELYNOI_POLYGON_H
#define DELYNOI_POLYGON_H

#include <vector>
#include <delynoi/models/basic/Point.h>
#include <delynoi/models/basic/Segment.h>
#include <delynoi/utilities/geometryFunctions.h>
#include <delynoi/utilities/convexHull.h>
#include <delynoi/models/basic/IndexSegment.h>
#include <utilities/Pair.h>
#include <map>
#include <utilities/UniqueList.h>
#include <algorithm>
#include <delynoi/models/neighbourhood/SegmentMap.h>

class Polygon {
protected:
    std::vector<int> points;
    double diameter;
    double area;
    Point centroid;

    double calculateDiameter(std::vector<Point>& p);
    double calculateArea(std::vector<Point>& p);
    Point calculateCentroid(std::vector<Point>& p);
    void calculateHash();
public:
    Polygon(std::vector<int>& points, std::vector<Point>& p);
    Polygon(std::vector<Point>& p);
    Polygon(const Polygon &obj);
    Polygon();

    double getDiameter();
    double getArea();
    Point getCentroid();
    void getSegments(std::vector<IndexSegment>& segments);
    std::vector<int> getPoints() const;
    std::vector<int>& getPoints();
    std::vector<Point> getPoints(std::vector<Point> p);
    int numberOfSides() const;
    bool operator==(const Polygon& other) const;
    bool operator<(const Polygon& other) const;
    std::string getString();

    void mutate(std::vector<Point>& p);

    bool containsPoint(std::vector<Point>& p, Point point);
    bool inEdges(std::vector<Point>& p, Point point);
    double signedArea(std::vector<Point>& p);
    bool containsEdge(IndexSegment s);

    bool isConvex(std::vector<Point>& p);
    bool isClockwise(std::vector<Point>& p);
    bool isVertex(int index);
    bool isSelfIntersecting(std::vector<Point> points);
    std::size_t hash;
    void fixCCW(std::vector<Point> p);

    IndexSegment containerEdge(std::vector<Point>& p, Point point);
    Point getAverage(std::vector<Point> p);
};

#endif