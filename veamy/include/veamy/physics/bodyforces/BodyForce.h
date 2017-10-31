#ifndef VEAMY_BODYFORCE_H
#define VEAMY_BODYFORCE_H

#include <veamy/utilities/functions_types.h>
#include <veamy/utilities/Computable.h>
#include <veamy/utilities/FunctionComputable.h>


class BodyForce{
protected:
    Computable* fX;
    Computable* fY;
public:
    BodyForce(func fX, func fY);
    BodyForce();

    Computable* getX();
    Computable* getY();
};

#endif