#ifndef DELYNOI_POINTMAP_H
#define DELYNOI_POINTMAP_H

#include <unordered_map>
#include <vector>
#include <delynoi/models/basic/Point.h>
#include <delynoi/models/neighbourhood/NeighboursByPoint.h>

struct PointHasher {
    std::size_t operator()(const Point &k) const {
        using std::size_t;
        using std::hash;

        return utilities::hash32(k.getX()) | (utilities::hash32(k.getY()) << 15);
    }
};

class PointMap {
private:
    std::unordered_map<Point, NeighboursByPoint, PointHasher> map;
public:
    PointMap();
    void insert(Point p, int neighbour);
    NeighboursByPoint& get(Point p);
    std::unordered_map<Point, NeighboursByPoint, PointHasher>& getMap();
    int size();
};

#endif