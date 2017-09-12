#include <delynoi/models/neighbourhood/NeighboursByPoint.h>

NeighboursByPoint::NeighboursByPoint() {}

NeighboursByPoint::NeighboursByPoint(int n) {
    this->neighbours.push_back(n);
}

NeighboursByPoint::NeighboursByPoint(std::vector<int> n) {
    this->neighbours.assign(n.begin(), n.end());
}

void NeighboursByPoint::add(int n) {
    this->neighbours.push_back(n);
}
