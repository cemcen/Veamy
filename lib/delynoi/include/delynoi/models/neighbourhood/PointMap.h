#ifndef DELYNOI_POINTMAP_H
#define DELYNOI_POINTMAP_H

#include <map>
#include <vector>
#include <delynoi/models/basic/Point.h>
#include <delynoi/models/neighbourhood/NeighboursByPoint.h>
#include <fstream>

class PointMap {
protected:
    std::map<Point, NeighboursByPoint> map;
public:
    PointMap();
    void insert(Point p, int neighbour);
    void insert(Point p, std::vector<int> neighbours);
    NeighboursByPoint& get(Point p);
    std::map<Point, NeighboursByPoint>& getMap();
    int size();
    void printInFile(std::string fileName);
};

#endif