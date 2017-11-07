#ifndef VEAMY_FUNCTIONCOMPUTABLE_H
#define VEAMY_FUNCTIONCOMPUTABLE_H

#include "Computable.h"
#include <veamy/utilities/functions_types.h>
#include <delynoi/models/polygon/Polygon.h>

class FunctionComputable : public Computable<Polygon>{
private:
    func f;
public:
    FunctionComputable(func f);
    double apply(double x, double y, int index, Polygon container);
};

#endif