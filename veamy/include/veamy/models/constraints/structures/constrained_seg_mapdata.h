#ifndef VEAMY_CONSTRAINMAPDATA_H
#define VEAMY_CONSTRAINMAPDATA_H

#include <mesher/models/basic/Segment.h>

struct intHasher {
    std::size_t operator()(const int &k) const {
        using std::size_t;
        using std::hash;

        return utilities::hash32(k);
    }
};

#endif
