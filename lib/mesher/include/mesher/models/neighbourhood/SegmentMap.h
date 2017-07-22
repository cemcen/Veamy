#ifndef MESHER_SEGMENTMAP_H
#define MESHER_SEGMENTMAP_H


#include <mesher/voronoi/structures/mapdata.h>
#include <utilities/Pair.h>
#include <unordered_map>
#include "Neighbours.h"
#include <fstream>
#include <mesher/models/basic/IndexSegment.h>

struct NeighboursHasher{
    std::size_t operator()(const Neighbours &k) const {
        return utilities::hash32(k.getFirst()) + utilities::hash32(k.getSecond());
    }
};

class SegmentMap{
private:
    std::unordered_map<IndexSegment,Neighbours,SegmentHasher> map;
public:
    SegmentMap();
    void insert(IndexSegment s, int polygonIndex);
    void insert(IndexSegment s, Neighbours n);
    void replace_neighbour(IndexSegment s, int oldNeighbour, int newNeighbour);
    void replace_or_delete(IndexSegment s, int oldNeighbour_current, int oldNeighbour_old, int newNeighbour,
                               std::unordered_map<Neighbours, int, NeighboursHasher> map,
                               std::unordered_map<IndexSegment, int, SegmentHasher> &erased,
                               std::unordered_map<int, int> newEquivalence);
    void insert_if_null(IndexSegment s, int index);
    Neighbours& get(IndexSegment s);
    std::unordered_map<IndexSegment,Neighbours,SegmentHasher>& getMap();
    int size();
    void delete_element(IndexSegment key);
    void printInFile(std::string fileName);
    bool containsSegment(IndexSegment s);

};

#endif 
