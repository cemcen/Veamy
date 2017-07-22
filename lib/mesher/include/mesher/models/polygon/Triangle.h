#ifndef MESHER_TRIANGLE_H
#define MESHER_TRIANGLE_H

#include <mesher/models/polygon/Polygon.h>
#include <mesher/models/neighbourhood/EdgeData.h>
#include <mesher/voronoi/structures/mapdata.h>
#include <unordered_map>

class Triangle : public Polygon{
private:
    Point circumcenter;
    Point calculateCircumcenter(std::vector<Point>& p);
public:
    Triangle();
    Triangle(std::vector<int> points, std::vector<Point>& p);
    Point getCircumcenter();
    int nextEdge(int center, EdgeData edge, std::unordered_map<Key, int, KeyHasher> edgeMap);
    int thirdPoint(EdgeData edge);
};

#endif


