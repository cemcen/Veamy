#ifndef VEAMY_STRAINVALUE_H
#define VEAMY_STRAINVALUE_H

#include <utilities/Trio.h>
#include <delynoi/models/basic/Point.h>
#include <veamy/utilities/functions_types.h>

class StrainValue {
private:
    func_trio f;
public:
    StrainValue(func_trio f);
    Trio<double> getValue(Point p);
};

#endif