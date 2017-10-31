#ifndef DELYNOI_TRIANGLE_H
#define DELYNOI_TRIANGLE_H

#include <delynoi/models/polygon/Polygon.h>
#include <delynoi/models/neighbourhood/EdgeData.h>
#include <delynoi/voronoi/structures/mapdata.h>
#include <unordered_map>

class Triangle : public Polygon {
private:
    Point circumcenter;
    Point calculateCircumcenter(std::vector<Point>& p);
public:
    Triangle();
    Triangle(std::vector<int> points, std::vector<Point>& p);
    Point getCircumcenter();
    int nextEdge(int center, EdgeData edge, std::unordered_map<Key, int, KeyHasher> edgeMap);
    int thirdPoint(EdgeData edge);
    bool isNull();
};

#endif


