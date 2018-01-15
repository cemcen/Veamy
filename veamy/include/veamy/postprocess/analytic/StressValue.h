#ifndef VEAMY_STRESSVALUE_H
#define VEAMY_STRESSVALUE_H

#include <utilities/Trio.h>
#include <delynoi/models/basic/Point.h>
#include <veamy/utilities/functions_types.h>

/*
 * Models the analytical stress solution for norm calculation
 */
class StressValue {
private:
    /*
     * Pointer to the function that represents the solution
     */
    func_pair f;
public:
    /*
     * Constructor
     */
    StressValue(func_pair f);

    /* Evaluates the solution function at a given point
     * @param p point to evaluate on
     * @return value of the real displacement on p
     */
    std::vector<double> getValue(Point p);
};

#endif