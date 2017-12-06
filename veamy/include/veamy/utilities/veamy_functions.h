#ifndef VEAMY_VEAMY_FUNCTIONS_H
#define VEAMY_VEAMY_FUNCTIONS_H

#include <delynoi/models/basic/Point.h>
#include <delynoi/models/polygon/Polygon.h>
#include <veamy/utilities/functions_types.h>
#include <veamy/postprocess/computables/Computable.h>
#include <veamy/lib/Eigen/Dense>

namespace veamy_functions{
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

    template <typename T>
    Eigen::VectorXd to_vector(Trio<T> vector){
        Eigen::VectorXd result = Eigen::VectorXd::Zero(3);
        result(0) = vector.first;
        result(1) = vector.second;
        result(2) = vector.third;

        return result;
    }

    template <typename T>
    Eigen::VectorXd to_vector(Pair<T> vector){
        Eigen::VectorXd result = Eigen::VectorXd::Zero(2);
        result(0) = vector.first;
        result(1) = vector.second;

        return result;
    }

    template <typename T>
    Trio<T> to_trio(Eigen::VectorXd vector){
        Trio<T> trio (vector(0), vector(1), vector(2));
        return trio;
    }

    extern double none_function(double x, double y);
}

#endif