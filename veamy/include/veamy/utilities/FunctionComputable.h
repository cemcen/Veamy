#ifndef VEAMY_FUNCTIONCOMPUTABLE_H
#define VEAMY_FUNCTIONCOMPUTABLE_H

#include "Computable.h"
#include "functions_types.h"

class FunctionComputable : public Computable{
private:
    func f;
public:
    FunctionComputable(func f);
    double apply(double x, double y, int index);
};

#endif