#ifndef VEAMY_FEAMYADDITIONALINFO_H
#define VEAMY_FEAMYADDITIONALINFO_H

#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <delynoi/models/basic/Point.h>
#include <vector>
#include <veamy/lib/Eigen/Dense>

struct FeamyAdditionalInfo{
    ShapeFunctions* N;
    std::vector<Point> points;
    Eigen::MatrixXd C;

    FeamyAdditionalInfo(ShapeFunctions* n, std::vector<Point> p, Eigen::MatrixXd CMatrix){
        N = n;
        points = p;
        C = CMatrix;
    }
};

#endif