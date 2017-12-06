#ifndef VEAMY_DISPLACEMENTVALUE_H
#define VEAMY_DISPLACEMENTVALUE_H

#include <utilities/Pair.h>
#include <delynoi/models/basic/Point.h>
#include <veamy/utilities/functions_types.h>

class DisplacementValue {
private:
    func_pair f;
public:
    DisplacementValue(func_pair f);
    Pair<double> getValue(Point p);
};

#endif