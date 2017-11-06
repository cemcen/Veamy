#ifndef VEAMY_DISPCOMPUTABLE_H
#define VEAMY_DISPCOMPUTABLE_H

#include <veamy/postprocess/analytic/DisplacementValue.h>
#include <veamy/postprocess/computables/Computable.h>
#include <delynoi/models/polygon/Polygon.h>

class DisplacementComputable : public Computable<Polygon> {
private:
    DisplacementValue* value;
public:
    DisplacementComputable(DisplacementValue* value);
    double apply(double x, double y, int index, Polygon container);
};

#endif