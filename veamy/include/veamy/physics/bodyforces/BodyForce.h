#ifndef VEAMY_BODYFORCE_H
#define VEAMY_BODYFORCE_H

#include <veamy/utilities/functions_types.h>
#include <veamy/postprocess/computables/Computable.h>
#include <veamy/postprocess/computables/FunctionComputable.h>

/*
 * Abstract class that models a body force (right hand side of the linear elasticity equation),
 * forces applied to the entire domain
 */
class BodyForce{
protected:
    /*
     * Functions that represent the body force in each axis
     */
    FunctionComputable* fX;
    FunctionComputable* fY;
public:
    /*
     * Constructor
     */
    BodyForce(func fX, func fY);

    /*
     * Default constructor
     */
    BodyForce();

    /*
     * @return function related to the x-axis
     */
    FunctionComputable* getX();

    /*
     * @return function related to the y-axis
     */
    FunctionComputable* getY();
};

#endif