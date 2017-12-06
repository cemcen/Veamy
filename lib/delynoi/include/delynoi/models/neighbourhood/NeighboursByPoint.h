#ifndef DELYNOI_NEIGHBOURSBYPOINT_H
#define DELYNOI_NEIGHBOURSBYPOINT_H

#include <vector>

class NeighboursByPoint {
private:
    std::vector<int> neighbours;
public:
    NeighboursByPoint();
    NeighboursByPoint(int n);
    NeighboursByPoint(std::vector<int> n);

    void add(int n);
    void insert(std::vector<int> n);
    std::vector<int> getNeighbours() const;
    std::vector<int>& getNeighbours();
};

#endif