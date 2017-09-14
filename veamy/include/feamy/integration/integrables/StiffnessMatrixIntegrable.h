#ifndef VEAMY_STIFFNESSMATRIXINTEGRABLE_H
#define VEAMY_STIFFNESSMATRIXINTEGRABLE_H

#include <veamy/lib/Eigen/Dense>
#include <feamy/integration/integrables/IntegrableFunction.h>
#include <veamy/geometry/VeamyTriangle.h>
#include <feamy/models/shapefunctions/ShapeFunctions.h>

class StiffnessMatrixIntegrable : public IntegrableFunction<Eigen::MatrixXd>{
private:
    ShapeFunctions* N;
    Eigen::MatrixXd J;
    Eigen::MatrixXd D;
public:
    StiffnessMatrixIntegrable(VeamyTriangle t, std::vector<Point> points, Eigen::MatrixXd D, ShapeFunctions* N);
    Eigen::MatrixXd apply(Point p);
};

#endif