#ifndef VEAMY_ISCONSTRAINEDINFO_H
#define VEAMY_ISCONSTRAINEDINFO_H

#include <delynoi/models/basic/IndexSegment.h>

/*
 * Structure that contains the information about the constraint state of a degree of freedom
 */
struct isConstrainedInfo{
    /*
     * Is the degree of freedom constrained?
     */
    bool isConstrained;
    /*
     * Container of the degree of freedom
     */
    IndexSegment container;

    /*
     * Constructor
     */
    isConstrainedInfo(IndexSegment c){
        isConstrained = true;
        container = c;
    }

    /*
     * Default constructor
     */
    isConstrainedInfo(){
        isConstrained = false;
    }

    /*
     * Sets the constrained flag as true
     */
    isConstrainedInfo(bool i){
        isConstrained = true;
    }
};


#endif
