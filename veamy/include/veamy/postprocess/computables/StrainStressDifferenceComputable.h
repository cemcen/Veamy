#ifndef VEAMY_STRAINSTRESSDIFFERENCECOMPUTABLE_H
#define VEAMY_STRAINSTRESSDIFFERENCECOMPUTABLE_H

#include <veamy/postprocess/analytic/StrainValue.h>
#include <veamy/postprocess/analytic/StressValue.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/dof/DOFS.h>
#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include "Computable.h"
#include <feamy/integration/integrables/StiffnessMatrixIntegrable.h>
#include <veamy/utilities/veamy_functions.h>


class StrainStressDifferenceComputable : public Computable<Triangle>{
private:
    StrainValue* strainValue;
    StressValue* stressValue;

    Eigen::VectorXd nodalValues;
    Eigen::MatrixXd C;
    DOFS dofs;
    ShapeFunctions* N;
    std::vector<Point> points;
public:
    StrainStressDifferenceComputable(StrainValue *strain, StressValue *stress,
                                     Eigen::VectorXd u, DOFS d, ShapeFunctions *N,
                                     std::vector<Point> p, Eigen::MatrixXd C);
    double apply(double x, double y, int index, Triangle container);
};

#endif