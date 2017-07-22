#ifndef MESHER_RECTANGLE_H
#define MESHER_RECTANGLE_H

#include <mesher/models/basic/Point.h>
#include <mesher/models/basic/PointSegment.h>
#include <mesher/models/Mesh.h>
#include <mesher/models/polygon/Polygon.h>

class BoundingBox {
private:
    Point p1;
    Point p2;

    std::vector<Point> getPoints();
public:
    BoundingBox(Point p1, Point p2);

    Point getFirst() const;
    Point getSecond() const;

    double getWidth();
    double getHeight();
    double xMin();
    double yMin();
    double xMax();
    double yMax();

    bool operator==(const BoundingBox& other) const;
    bool contains(Point p);
    void getSegments(std::vector<PointSegment>& segments);
    bool fitsInsidePolygon(Polygon poly, std::vector<Point> points);
    bool intersects(BoundingBox box);
    Point getClosestTo(Point p);
    Point centroid();
};


#endif
