#ifndef VEAMY_DISPCOMPUTABLE_H
#define VEAMY_DISPCOMPUTABLE_H

#include <veamy/postprocess/analytic/DisplacementValue.h>
#include <veamy/utilities/Computable.h>

class DisplacementComputable : public Computable {
private:
    DisplacementValue* value;
public:
    DisplacementComputable(DisplacementValue* value);
    double apply(double x, double y, int index);
};

#endif