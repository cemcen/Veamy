#ifndef VEAMY_DISPLACEMENTVALUE_H
#define VEAMY_DISPLACEMENTVALUE_H

#include <utilities/Pair.h>
#include <delynoi/models/basic/Point.h>
#include <veamy/utilities/functions_types.h>

/*
 * Models the analytical displacement solution for norm calculation
 */
class DisplacementValue {
private:
    /*
     * Pointer to the function that represents the solution
     */
    func_pair f;
public:
    /*
     * Constructor
     */
    DisplacementValue(func_pair f);

    /* Evaluates the solution function at a given point
     * @param p point to evaluate on
     * @return value of the real displacement on p
     */
    Pair<double> getValue(Point p);
};

#endif