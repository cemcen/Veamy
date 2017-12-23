#ifndef VEAMY_GAUSSPOINTS_H
#define VEAMY_GAUSSPOINTS_H

#include <vector>
#include <delynoi/models/basic/Point.h>

/*
 * Namespace which contain functions related to the gaussian quadratures
 */
namespace gauss_quadrature{
    /*
     * Sets in two given vectors the quadrature points and weights of a line
     * @param order order of the quadrature
     * @param points,weights vectors where the points and weights will be set
     */
    extern void gauss_1d(int order, std::vector<double>& points, std::vector<double>& weights);

    /*
     * Sets in two given vectors the quadrature points and weights of a triangle
     * @param order order of the quadrature
     * @param points,weights vectors where the points and weights will be set
     */
    extern void gauss_triangle(int order, std::vector<Point>& points, std::vector<double>& weights);
}


#endif