#ifndef VEAMY_SEGMENTPAIR_H
#define VEAMY_SEGMENTPAIR_H

#include <delynoi/models/basic/IndexSegment.h>

struct SegmentPair{
    IndexSegment s1;
    IndexSegment s2;

    SegmentPair(IndexSegment seg1, IndexSegment seg2){
        s1 = seg1;
        s2 = seg2;
    }

};

#endif
