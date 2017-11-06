#ifndef VEAMY_L2NORMCALCULATOR_H
#define VEAMY_L2NORMCALCULATOR_H

#include <veamy/postprocess/NormCalculator.h>
#include <veamy/postprocess/analytic/DisplacementValue.h>
#include <veamy/Veamer.h>
#include <feamy/Feamer.h>
#include <feamy/postprocess/integrator/FeamyIntegrator.h>
#include <veamy/postprocess/integrator/VeamyIntegrator.h>

class L2NormCalculator: public NormCalculator {
private:
    DisplacementValue* value;
public:
    L2NormCalculator(DisplacementValue* value, Eigen::VectorXd u, DOFS d);
    void setCalculators(NormIntegrator* integrator);
};

#endif