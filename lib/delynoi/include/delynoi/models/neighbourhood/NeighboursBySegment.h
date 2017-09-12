#ifndef DELYNOI_NEIGHBOURS_H
#define DELYNOI_NEIGHBOURS_H

#include <iostream>
#include <utilities/utilities.h>

class NeighboursBySegment {
private:
    int n1;
    int n2 = -1;
public:
    NeighboursBySegment();
    NeighboursBySegment(int i1);
    NeighboursBySegment(int i1, int i2);
    NeighboursBySegment(Pair<int> p);
    void setNeighbour(int i);
    int getFirst() const;
    int getSecond() const;
    std::string getString() const;
    bool operator==(const NeighboursBySegment& other) const;
};


#endif 
