#ifndef VEAMY_STRAINSTRESSDIFFERENCECOMPUTABLE_H
#define VEAMY_STRAINSTRESSDIFFERENCECOMPUTABLE_H

#include <veamy/postprocess/analytic/StrainValue.h>
#include <veamy/postprocess/analytic/StressValue.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/dof/DOFS.h>
#include "Computable.h"
#include <feamy/integration/integrables/StiffnessMatrixIntegrable.h>
#include <veamy/utilities/veamy_functions.h>
#include <feamy/models/FeamyElement.h>

template <typename T>
class StrainStressDifferenceComputable : public Computable<T>{
private:
    StrainValue* strainValue;
    StressValue* stressValue;

    Eigen::VectorXd nodalValues;
    Eigen::MatrixXd C;
    DOFS dofs;
    std::vector<FeamyElement*> elements;
    std::vector<Point> points;
    int polygonIndex;
public:
    StrainStressDifferenceComputable(StrainValue *strain, StressValue *stress,
                                     Eigen::VectorXd u, DOFS d, std::vector<FeamyElement*> elements,
                                     std::vector<Point> p, Eigen::MatrixXd C);
    double apply(double x, double y, int index, T container);
    void setPolygonIndex(int polyIndex);
};

#endif