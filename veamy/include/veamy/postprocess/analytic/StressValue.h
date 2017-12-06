#ifndef VEAMY_STRESSVALUE_H
#define VEAMY_STRESSVALUE_H

#include <utilities/Trio.h>
#include <delynoi/models/basic/Point.h>
#include <veamy/utilities/functions_types.h>


class StressValue {
private:
    func_trio f;
public:
    StressValue(func_trio f);
    Trio<double> getValue(Point p);
};

#endif