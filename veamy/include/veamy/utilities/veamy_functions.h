#ifndef VEAMY_VEAMY_FUNCTIONS_H
#define VEAMY_VEAMY_FUNCTIONS_H

#include <delynoi/models/basic/Point.h>
#include <delynoi/models/polygon/Polygon.h>
#include <veamy/utilities/functions_types.h>
#include "Computable.h"

namespace veamy_functions{
    extern double volume_nodal_quadrature(Polygon poly, std::vector<Point> points, Computable* f);
}

#endif