#ifndef VEAMY_H1NORMCALCULATOR_H
#define VEAMY_H1NORMCALCULATOR_H

#include <veamy/postprocess/NormCalculator.h>
#include <veamy/postprocess/analytic/StrainValue.h>
#include <veamy/postprocess/analytic/StressValue.h>
#include <feamy/postprocess/integrator/FeamyIntegrator.h>
#include <veamy/postprocess/computables/StrainStressDifferenceComputable.h>
#include <veamy/postprocess/computables/StrainStressComputable.h>

class H1NormCalculator : public NormCalculator {
private:
    StressValue* stressValue;
    StrainValue* strainValue;
public:
    H1NormCalculator(StrainValue *strain, StressValue *stress, Eigen::VectorXd u, DOFS d,
                         std::vector<Point> points);
    void setCalculator(NormIntegrator* integrator);

    void setCalculator(FeamyIntegrator* integrator);
    void setCalculator(VeamyIntegrator* integrator);
};

#endif