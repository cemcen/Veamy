#ifndef VEAMY_BODYFORCE_H
#define VEAMY_BODYFORCE_H

#include <veamy/utilities/functions_types.h>
#include <veamy/postprocess/computables/Computable.h>
#include <veamy/postprocess/computables/FunctionComputable.h>


class BodyForce{
protected:
    FunctionComputable* fX;
    FunctionComputable* fY;
public:
    BodyForce(func fX, func fY);
    BodyForce();

    FunctionComputable* getX();
    FunctionComputable* getY();
};

#endif