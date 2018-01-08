#ifndef VEAMY_VEAMY_FUNCTIONS_H
#define VEAMY_VEAMY_FUNCTIONS_H

#include <delynoi/models/basic/Point.h>
#include <delynoi/models/polygon/Polygon.h>
#include <veamy/utilities/functions_types.h>
#include <veamy/postprocess/computables/Computable.h>
#include <veamy/lib/Eigen/Dense>
#include <delynoi/triangulation/CenterTriangulationGenerator.h>
#include <delynoi/triangulation/EarTriangulationGenerator.h>
#include <feamy/integration/quadrature/gauss_quadrature.h>

/*
 * Namespace that define a number of utility functions of the Veamy library
 */
namespace veamy_functions{
    /* Computes a numerical integral approximation using a nodal quadrature scheme
     *  @param poly polygon in which the integral will be computed
     *  @param points mesh points
     *  @param f computable representing the function to integrate
     */
    template <typename T>
    double nodal_quadrature(T poly, std::vector<Point> points, Computable<T>* f){
        double result = 0;
        std::vector<int> polygonPoints = poly.getPoints();
        int n = (int) polygonPoints.size();

        IndexSegment prev;
        IndexSegment next;

        for (int i = 0; i < n; ++i) {
            prev = IndexSegment(polygonPoints[(n+i-1)%n], polygonPoints[i]);
            next = IndexSegment(polygonPoints[i], polygonPoints[(i+1)%n]);

            Point point = points[polygonPoints[i]];
            std::vector<Point> smallPolygon = {prev.middlePoint(points), points[polygonPoints[i]],
                                               next.middlePoint(points), poly.getCentroid()};

            double area = geometry_functions::area(smallPolygon);

            result += area*f->apply(point.getX(), point.getY(), polygonPoints[i], poly);
        }

        return result;
    }

    /* Computes a numerical integral approximation using a Gaussian scheme
     * @param poly polygon in which the integral will be computed
     * @param points mesh points
     */
    extern double gauss_integration(Polygon poly, std::vector<Point>& points, int nGauss,
                                      Computable<Polygon>* computable);

    /* Converts a Trio to an Eigen vector
     * @param vector Trio to convert
     * @return the same values, in an Eigen vector
     */
    template <typename T>
    Eigen::VectorXd to_vector(Trio<T> vector){
        Eigen::VectorXd result = Eigen::VectorXd::Zero(3);
        result(0) = vector.first;
        result(1) = vector.second;
        result(2) = vector.third;

        return result;
    }

    /* Converts a Pair to an Eigen vector
     * @param vector Pair to convert
     * @return the same values, in an Eigen vector
     */
    template <typename T>
    Eigen::VectorXd to_vector(Pair<T> vector){
        Eigen::VectorXd result = Eigen::VectorXd::Zero(2);
        result(0) = vector.first;
        result(1) = vector.second;

        return result;
    }

    /* Converts an Eigen vector to a Trio
     * @param vector vector to convert
     * @return the same values, in a Trio
     */
    template <typename T>
    Trio<T> to_trio(Eigen::VectorXd vector){
        Trio<T> trio (vector(0), vector(1), vector(2));
        return trio;
    }

    /*
     * Defines a function that always returns zero, used for body forces
     * @param x y params of the function (not used, left to have the same signature as all body forces functions)
     * @return zero
     */
    extern double none_function(double x, double y);

}

#endif