#ifndef VEAMY_BODYFORCE_H
#define VEAMY_BODYFORCE_H

#include <veamy/utilities/functions_types.h>
#include <veamy/postprocess/computables/Computable.h>
#include <veamy/postprocess/computables/FunctionComputable.h>

/*
 * Abstract class that models a body force (right hand side), forces applied to the entire domain
 */
class BodyForce{
protected:
    /*
     * Functions that represent the body force
     */
    std::vector<FunctionComputable*> f;

    /*
     * Number of components of the body force function
     */
    int components;
public:
    /*
     * Constructor
     */
    BodyForce(func fX, func fY);

    /*
     * Constructor
     */
    BodyForce(func f);

    /*
     * Default constructor
     */
    BodyForce();

    /*
     * @return functions representing this bodyforce
     */
    std::vector<FunctionComputable*> getComponents();

    /*
     *
     */
    int numberOfComponents();
};

#endif