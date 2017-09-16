#ifndef VEAMY_GAUSSPOINTS_H
#define VEAMY_GAUSSPOINTS_H

#include <vector>
#include <delynoi/models/basic/Point.h>

namespace gauss_quadrature{
    extern void gauss_1d(int order, std::vector<double>& points, std::vector<double>& weights);
    extern void gauss_triangle(int order, std::vector<Point>& points, std::vector<double>& weights);
}


#endif