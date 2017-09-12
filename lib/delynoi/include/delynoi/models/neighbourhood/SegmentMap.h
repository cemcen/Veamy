#ifndef DELYNOI_SEGMENTMAP_H
#define DELYNOI_SEGMENTMAP_H

#include <delynoi/voronoi/structures/mapdata.h>
#include <utilities/Pair.h>
#include <unordered_map>
#include "NeighboursBySegment.h"
#include <fstream>
#include <delynoi/models/basic/IndexSegment.h>

struct NeighboursHasher{
    std::size_t operator()(const NeighboursBySegment &k) const {
        return utilities::hash32(k.getFirst()) + utilities::hash32(k.getSecond());
    }
};

class SegmentMap{
private:
    std::unordered_map<IndexSegment,NeighboursBySegment,SegmentHasher> map;
public:
    SegmentMap();
    void insert(IndexSegment s, int polygonIndex);
    void insert(IndexSegment s, NeighboursBySegment n);
    NeighboursBySegment& get(IndexSegment s);
    std::unordered_map<IndexSegment,NeighboursBySegment,SegmentHasher>& getMap();
    int size();
    void printInFile(std::string fileName);
    bool containsSegment(IndexSegment s);

};

#endif 
