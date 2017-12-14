#ifndef VEAMY_COMPUTABLE_H
#define VEAMY_COMPUTABLE_H

/*
 * Abstract class that models the calculations of the minimal terms of the norms (the values inside the integrals, that
 * later are numerically integrated)
 */
template <typename T>
class Computable {
public:
    /* Calculates the value of this particular computable on a point
     * @param x y coordinates of the point
     * @param index index of the point (if part of the mesh)
     * @param container geometric container of the point
     * @return value of the computable
     */
    virtual double apply(double x, double y, int index, T container) = 0;

    /* Sets the index of the polygon in which the next points will be contained
     * @param polyIndex index of the polygon
     */
    virtual void setPolygonIndex(int polyIndex){}
};

#endif