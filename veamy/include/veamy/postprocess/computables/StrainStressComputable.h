#ifndef VEAMY_STRAINSTRESSCOMPUTABLE_H
#define VEAMY_STRAINSTRESSCOMPUTABLE_H

#include <veamy/postprocess/analytic/StrainValue.h>
#include <veamy/postprocess/analytic/StressValue.h>
#include <delynoi/models/polygon/Triangle.h>
#include "Computable.h"

template <typename T>
class StrainStressComputable : public Computable<T>{
private:
    StrainValue* strainValue;
    StressValue* stressValue;
public:
    StrainStressComputable(StrainValue* strain, StressValue* value);
    double apply(double x, double y, int index, T container);
};

#endif