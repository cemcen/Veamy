#ifndef DELYNOI_EDGEDATA_H
#define DELYNOI_EDGEDATA_H

#include <iostream>
#include <utilities/utilities.h>

/*
 * Class that models the neighbourhood information of a Delaunay triangulation (segment represnted by two points and the
 * two incident triangles).
 */
class EdgeData{
public:
    /*
     * Information contained (segment and incident triangles, refered by their indexes)
     */
    int p1;
    int p2;
    int t1;
    int t2;

    /*
     * Constructor.
     */
    EdgeData(int p1, int p2);

    /* Sets a new incident triangle to this segment
     * @param t trinagle index to set as incident
     */
    void setTriangle(int t);

    /*
     * @return string representation of the data of the class
     */
    std::string getString();

    /*
     * Equality operator.
     * @param other EdgeData to compare
     * @return if the two EdgeData instances are equal
     */
    bool operator==(const EdgeData& other) const;
};

#endif
