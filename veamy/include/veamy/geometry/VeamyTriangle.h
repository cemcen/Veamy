#ifndef VEAMY_VEAMYTRIANGLE_H
#define VEAMY_VEAMYTRIANGLE_H

#include <delynoi/models/polygon/Triangle.h>
#include <veamy/lib/Eigen/Dense>

class VeamyTriangle: public Triangle {
public:
    VeamyTriangle();
    VeamyTriangle(Triangle t);
    VeamyTriangle(int p1, int p2, int p3);
    std::vector<VeamyTriangle> triangulate(std::vector<Point> points);
    Eigen::MatrixXd getJacobian(std::vector<Point> points);
    bool isNull();
    int indexOf(int i);
};

#endif