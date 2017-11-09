#ifndef VEAMY_DISPDIFFERENCECOMPUTABLE_H
#define VEAMY_DISPDIFFERENCECOMPUTABLE_H

#include <veamy/postprocess/analytic/DisplacementValue.h>
#include <veamy/postprocess/computables/Computable.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/dof/DOFS.h>
#include <veamy/postprocess/calculators/DisplacementCalculator.h>

template <typename T>
class DisplacementDifferenceComputable : public Computable<T>{
private:
    DisplacementValue* value;
    Eigen::VectorXd nodalValues;
    DOFS dofs;
    DisplacementCalculator<T>* calculator;
    int polygonIndex;
public:
    DisplacementDifferenceComputable(DisplacementValue *v, DisplacementCalculator<T>* calculator);
    double apply(double x, double y, int index, T container);
    void setPolygonIndex(int polyIndex);
};

#endif