#include <delynoi/models/neighbourhood/PointMap.h>

PointMap::PointMap() {}

void PointMap::insert(Point p, int neighbour) {
    auto got = this->map.find(p);

    if(got == this->map.end()){
        NeighboursByPoint n (neighbour);
        this->map.insert(std::make_pair(p,n));
    }else{
        NeighboursByPoint& n = got->second;
        n.add(neighbour);
    }
}

NeighboursByPoint &PointMap::get(Point p) {
    return this->map[p];
}

std::unordered_map<Point, NeighboursByPoint, PointHasher> &PointMap::getMap() {
    return this->map;
}

int PointMap::size() {
    return 0;
}
