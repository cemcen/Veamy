#ifndef VEAMY_L2NORMCALCULATOR_H
#define VEAMY_L2NORMCALCULATOR_H

#include <veamy/postprocess/NormCalculator.h>
#include <veamy/postprocess/analytic/DisplacementValue.h>
#include <feamy/postprocess/integrator/FeamyIntegrator.h>
#include <veamy/postprocess/integrator/VeamyIntegrator.h>
#include <feamy/postprocess/structures/FeamyAdditionalInfo.h>

template <typename T>
class L2NormCalculator: public NormCalculator<T> {
private:
    DisplacementValue* value;
public:
    L2NormCalculator(DisplacementValue* value, Eigen::VectorXd u, DOFS d);
    void setCalculator(FeamyIntegrator<T>* integrator, FeamyAdditionalInfo info);
    void setCalculator(VeamyIntegrator<T>* integrator);
};

#endif