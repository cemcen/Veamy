#ifndef DELYNOI_NEIGHBOURS_H
#define DELYNOI_NEIGHBOURS_H

#include <iostream>
#include <utilities/utilities.h>

/*
 * Class that models polygon neighbourhood by segment, meaning, the two (or one in case it is a boundary segment) that share
 * a segment.
 */
class NeighboursBySegment {
private:
    /*
     * Indexes of the polygons that contain a segment
     */
    int n1;
    int n2 = -1;
public:
    /*
     * Default constructor
     */
    NeighboursBySegment();

    /*
     * Constructor. Sets one of the two polygons
     */
    NeighboursBySegment(int i1);

    /*
     * Constructor. Sets both incident polygons
     */
    NeighboursBySegment(int i1, int i2);

    /*
     * Constructor. Sets both incident polygons, given as a pair
     */
    NeighboursBySegment(Pair<int> p);

    /*
     * Sets a new neighbour
     * @param neighbour to set
     */
    void setNeighbour(int i);

    /*
     * @return first neighbour
     */
    int getFirst() const;

    /*
     * @return second neighbour
     */
    int getSecond() const;

    /*
     * Sets the neighbour in the first position
     * @param value neighbour to set
     */
    void setFirst(int value);

    /*
     * Sets the neighbour in the second position
     * @param value neighbour to set
     */
    void setSecond(int value);

    /*
     * @return the string representation of the class
     */
    std::string getString() const;

    /*
     * Equality operator
     * @param other NeighboursBySegment instance to compare against
     * @return whether the two instances are equal
     */
    bool operator==(const NeighboursBySegment& other) const;
};


#endif 
