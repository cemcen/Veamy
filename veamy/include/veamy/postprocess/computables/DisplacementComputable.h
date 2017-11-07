#ifndef VEAMY_DISPCOMPUTABLE_H
#define VEAMY_DISPCOMPUTABLE_H

#include <veamy/postprocess/analytic/DisplacementValue.h>
#include <veamy/postprocess/computables/Computable.h>
#include <delynoi/models/polygon/Polygon.h>
#include <delynoi/models/polygon/Triangle.h>

template <typename T>
class DisplacementComputable : public Computable<T> {
private:
    DisplacementValue* value;
public:
    DisplacementComputable(DisplacementValue* value);
    double apply(double x, double y, int index, T container);
};

#endif