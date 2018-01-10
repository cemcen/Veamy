#ifndef VEAMY_DOF_H
#define VEAMY_DOF_H

#include <utilities/Pair.h>
#include <delynoi/models/polygon/Polygon.h>

/*
 * Class that models a single degree of freedom
 */
class DOF {
protected:
    /*
     * Index of this DOF
     */
    int index;

    /*
     * Index of the point this DOF is associated to
     */
    int point_index;

    /*
     * Index of the direction (or axis) of this DOF. For example, in linear elasticity, x is 0 and y is 1
     */
    int d;
public:
    /*
     * Constructor, receives the index of the axis of this DOF (for vectorial problems)
     */
    DOF(int index, int point_index, int axis);

    /*
     * Constructor
     */
    DOF(int index, int point_index);

    /*
     * @return the index of this DOF in the complete system
     */
    int globalIndex() const;

    /*
     * @return the index of the point this DOF is associated to
     */
    int pointIndex();

    /*
     * Equality operator.
     * @param other DOF instance to compare against
     * @return if the two instances are equal (represent the same DOF)
     */
    bool operator==(const DOF& other) const;

    /* Lesser than operator.
     * @param other DOF instance to compare against
     * @return whether this DOF is lesser (in index and direction) than other
     */
    bool operator<(const DOF& other) const;

    /*
     * @return index of the axis of this DOF
     */
    int getAxis();
};

#endif
