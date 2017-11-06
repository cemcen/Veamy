#ifndef VEAMY_STRAINSTRESSCOMPUTABLE_H
#define VEAMY_STRAINSTRESSCOMPUTABLE_H

#include <veamy/postprocess/analytic/StrainValue.h>
#include <veamy/postprocess/analytic/StressValue.h>
#include <delynoi/models/polygon/Polygon.h>
#include "Computable.h"

class StrainStressComputable : public Computable<Polygon>{
private:
    StrainValue* strainValue;
    StressValue* stressValue;
public:
    StrainStressComputable(StrainValue* strain, StressValue* value);
    double apply(double x, double y, int index, Polygon container);
};

#endif