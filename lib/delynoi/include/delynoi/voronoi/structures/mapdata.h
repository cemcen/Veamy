#ifndef DELYNOI_MAPDATA_H
#define DELYNOI_MAPDATA_H

#include <functional>
#include <delynoi/models/basic/IndexSegment.h>

/*
 * Structure used as a key for the EdgeData map (used for the Voronoi diagram generation algorithm)
 */
struct Key {
    int first;
    int second;
    std::size_t hash;

    Key(int f, int s){
        first=f;
        second=s;
        hash=utilities::hash32(first) + utilities::hash32(second);
    }

    bool operator==(const Key &other) const{
        return first == other.first && second == other.second ||
               first == other.second && second == other.first;
    }
};

/*
 * Structure that is used to compute the hash value of the Key structure
 */
struct KeyHasher {
    std::size_t operator()(const Key &k) const {
        using std::size_t;
        using std::hash;

        return k.hash;
    }
};

/*
 * Structure that is used to compute the hash value of an IndexSegment, so that it can be used as key for
 * the SegmentMap
 */
struct SegmentHasher {
    std::size_t operator()(const IndexSegment &k) const {
        using std::size_t;
        using std::hash;

        return k.hash;
    }
};

#endif