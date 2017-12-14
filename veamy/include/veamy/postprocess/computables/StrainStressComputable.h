#ifndef VEAMY_STRAINSTRESSCOMPUTABLE_H
#define VEAMY_STRAINSTRESSCOMPUTABLE_H

#include <veamy/postprocess/analytic/StrainValue.h>
#include <veamy/postprocess/analytic/StressValue.h>
#include <delynoi/models/polygon/Triangle.h>
#include "Computable.h"

/*
 * Computes the term sigma dot epsilon of the H1 norm
 */
template <typename T>
class StrainStressComputable : public Computable<T>{
private:
    /*
     * Analytical strain value
     */
    StrainValue* strainValue;

    /*
     * Analytical stress value
     */
    StressValue* stressValue;
public:
    /*
     * Constructor
     */
    StrainStressComputable(StrainValue* strain, StressValue* value);

    /* Calculates the value of this particular computable on a point
     * @param x y coordinates of the point
     * @param index index of the point (if part of the mesh)
     * @param container geometric container of the point
     * @return value of the computable
     */
    double apply(double x, double y, int index, T container);
};

#endif