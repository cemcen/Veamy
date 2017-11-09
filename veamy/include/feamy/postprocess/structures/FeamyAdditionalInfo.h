#ifndef VEAMY_FEAMYADDITIONALINFO_H
#define VEAMY_FEAMYADDITIONALINFO_H

#include <feamy/models/FeamyElement.h>
#include <delynoi/models/basic/Point.h>
#include <vector>
#include <veamy/lib/Eigen/Dense>

struct FeamyAdditionalInfo{
    std::vector<FeamyElement*> elements;
    std::vector<Point> points;
    Eigen::MatrixXd C;

    FeamyAdditionalInfo(std::vector<FeamyElement*> e, std::vector<Point> p, Eigen::MatrixXd CMatrix){
        elements = e;
        points = p;
        C = CMatrix;
    }
};

#endif