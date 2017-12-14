#ifndef VEAMY_FUNCTIONCOMPUTABLE_H
#define VEAMY_FUNCTIONCOMPUTABLE_H

#include "Computable.h"
#include <veamy/utilities/functions_types.h>
#include <delynoi/models/polygon/Polygon.h>

/*
 * Defines a computable that wraps over a function pointer so that it can be integrated with the same tools as the rest
 * of the computables
 */
class FunctionComputable : public Computable<Polygon>{
private:
    /*
     * Function (pointer) to integrate
     */
    func f;
public:
    /*
     * Constructor
     */
    FunctionComputable(func f);

    /* Calculates the value of function on a point
     * @param x y coordinates of the point
     * @param index index of the point (if part of the mesh)
     * @param container geometric container of the point
     * @return value of the computable
     */
    double apply(double x, double y, int index, Polygon container);
};

#endif