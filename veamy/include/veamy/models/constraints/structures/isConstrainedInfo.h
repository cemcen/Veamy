#ifndef VEAMY_ISCONSTRAINEDINFO_H
#define VEAMY_ISCONSTRAINEDINFO_H

#include <mesher/models/basic/IndexSegment.h>

struct isConstrainedInfo{
    bool isConstrained;
    IndexSegment container;

    isConstrainedInfo(IndexSegment c){
        isConstrained = true;
        container = c;
    }

    isConstrainedInfo(){
        isConstrained = false;
    }
};


#endif
