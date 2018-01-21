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
#include <veamy/postprocess/utilities/norm_utilities.h>
#include <utilities/Trio.h>

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
                                               next.middlePoint(points), poly.getAverage(points)};

            double area = geometry_functions::area(smallPolygon);
            double res = f->apply(point.getX(), point.getY(), polygonPoints[i], poly);

            result += area*res;
        }

        return result;
    }

    /* Converts a standard vector to an Eigen vector
     * @param v vector to convert
     * @return the same values, in an Eigen vector
     */
    template <typename T>
    Eigen::VectorXd to_vector(std::vector<T> v){
        Eigen::VectorXd result = Eigen::VectorXd::Zero(v.size());

        for (int i = 0; i < v.size(); ++i) {
            result(i) = v[i];
        }

        return result;
    }

    /* Converts an Eigen vector to a standard vector
     * @param v vector to convert
     * @return the same values, in a standard vector
     */
    template <typename T>
    std::vector<T> to_std_vector(Eigen::VectorXd v){
        std::vector<T> result;

        for (int i = 0; i < v.size(); ++i) {
            result.push_back(v[i]);
        }

        return result;
    }

    /* Computes a numerical integral approximation using a Gaussian scheme
     * @param poly polygon in which the integral will be computed
     * @param points mesh points
     */
    template <typename T>
    double gauss_integration(T poly, std::vector<Point>& points, int nGauss, Computable<T>* computable){
        std::vector<Triangle> triangles;
        double result = 0;

        if(poly.isConvex(points)){
            triangles = CenterTriangulationGenerator().triangulate(poly, points);
        } else {
            triangles = EarTriangulationGenerator().triangulate(poly, points);
        }

        for (Triangle t: triangles){
            Eigen::MatrixXd gaussPoints;
            std::vector<double> weights;

            norm_utilities::triangle_rules(gaussPoints, t, weights, nGauss, points);

            for (int i = 0; i < weights.size(); ++i) {
                Point p = Point(gaussPoints(i,0), gaussPoints(i,1));

                result += computable->apply(p.getX(), p.getY(), 0, poly)*weights[i];
            }
        }

        return result;

    }

    /*
     * Defines a function that always returns zero, used for body forces
     * @param x y params of the function (not used, left to have the same signature as all body forces functions)
     * @return zero
     */
    extern double none_function(double x, double y);

    template <typename T>
    double dot(std::vector<T> v1, std::vector<T> v2){
        if(v1.size()!=v2.size()){
            throw std::invalid_argument("Can not compute the dot product between two vectors of different sizes");
        }

        double result = 0;

        for (int i = 0; i < v1.size(); ++i) {
            result += v1[i]*v2[i];
        }

        return result;
    }

    template <typename T>
    std::vector<T> substract(std::vector<T> v1, std::vector<T> v2){
        if(v1.size()!=v2.size()){
            throw std::invalid_argument("Can not compute the substraction between two vectors of different sizes");
        }

        std::vector<T> result;

        for (int i = 0; i < v1.size(); ++i) {
            result.push_back(v1[i] - v2[i]);
        }

        return result;
    }

}

#endif