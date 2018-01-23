#ifndef VEAMY_STRAINCOMPUTABLE_H
#define VEAMY_STRAINCOMPUTABLE_H

#include <veamy/postprocess/analytic/StrainValue.h>
#include <veamy/lib/Eigen/Dense>
#include "H1Computable.h"

/*
 * Computes the epsilon*sigma part of the H1 norm considering only the strain value
 */
template <typename T>
class StrainComputable: public H1Computable<T>{
private:
    /*
     * Analytical strain value
     */
    StrainValue* strainValue;
public:
    /*
     * Constructor
     */
    StrainComputable(StrainValue* strain);

    /* Calculates the value of this particular computable on a point
     * @param x y coordinates of the point
     * @param index index of the point (if part of the mesh)
     * @param container geometric container of the point
     * @return value of the computable
     */
    double apply(double x, double y, int index, T container);

};

#endif