#ifndef VEAMY_CALCULATORCONSTRUCTOR_H
#define VEAMY_CALCULATORCONSTRUCTOR_H

#include <veamy/postprocess/calculators/DisplacementCalculator.h>
#include <veamy/postprocess/calculators/StrainCalculator.h>
#include <veamy/postprocess/integrator/VeamyIntegrator.h>
#include <feamy/postprocess/integrator/FeamyIntegrator.h>

template <typename T>
class CalculatorConstructor {
public:
    virtual DisplacementCalculator<T> getDisplacementCalculator(VeamyIntegrator* v) = 0;
    virtual DisplacementCalculator<T> getDisplacementCalculator(FeamyIntegrator* f) = 0;

    virtual StrainCalculator<T> getStrainCalculator(VeamyIntegrator* v) = 0;
    virtual StrainCalculator<T> getStrainCalculator(FeamyIntegrator* f) = 0;
};

#endif