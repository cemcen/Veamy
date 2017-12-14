#ifndef VEAMY_SEGMENTPAIR_H
#define VEAMY_SEGMENTPAIR_H

#include <delynoi/models/basic/IndexSegment.h>

/*
 * Structure that contains a pair of segments, used as a commodity instead of having to pass both around
 */
struct SegmentPair{
    IndexSegment s1;
    IndexSegment s2;

    SegmentPair(IndexSegment seg1, IndexSegment seg2){
        s1 = seg1;
        s2 = seg2;
    }

};

#endif
