#ifndef VEAMY_STRAINVALUE_H
#define VEAMY_STRAINVALUE_H

#include <utilities/Trio.h>
#include <delynoi/models/basic/Point.h>
#include <veamy/utilities/functions_types.h>

/*
 * Models the analytical strain solution for norm calculation
 */
class StrainValue {
private:
    /*
     * Pointer to the function that represents the solution
     */
    func_pair f;
public:
    /*
     * Constructor
     */
    StrainValue(func_pair f);

    /* Evaluates the solution function at a given point
     * @param p point to evaluate on
     * @return value of the real displacement on p
     */
    std::vector<double> getValue(Point p);
};

#endif