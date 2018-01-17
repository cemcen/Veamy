#ifndef VEAMY_STRAINDIFFERENCECOMPUTABLE_H
#define VEAMY_STRAINDIFFERENCECOMPUTABLE_H

#include <veamy/postprocess/analytic/StrainValue.h>
#include "H1Computable.h"

/*
 *  Computes the term (epsilon - epsilonH)*D*(epsilon - epsilonH) of the H1 norm.
 */
template <typename T>
class StrainDifferenceComputable : public H1Computable<T>{
protected:
    /*
     * Analytical strain value
     */
    StrainValue* strainValue;

    /*
    * Index of the polygon that contains the points that will be used next
    */
    int polygonIndex;
public:
    StrainDifferenceComputable(StrainValue* value);

    /* Computes the value of the necessary term in a given point
     * @param p point to apply the function
     * @param t container of the point
     * @return the value of the function
     */
    double apply(double x, double y, int index, T container);

    /* Sets the index of the polygon in which the next points will be contained
     * @param polyIndex index of the polygon
     */
    void setPolygonIndex(int polyIndex);
};

#endif