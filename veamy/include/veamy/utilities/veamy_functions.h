#ifndef VEAMY_VEAMY_FUNCTIONS_H
#define VEAMY_VEAMY_FUNCTIONS_H

#include <delynoi/models/basic/Point.h>
#include <delynoi/models/polygon/Polygon.h>
#include <veamy/utilities/functions_types.h>
#include <veamy/postprocess/computables/Computable.h>
#include <veamy/lib/Eigen/Dense>

namespace veamy_functions{
    extern double nodal_quadrature(Polygon poly, std::vector<Point> points, Computable *f);

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

}

#endif