#ifndef VEAMY_H1NORMCALCULATOR_H
#define VEAMY_H1NORMCALCULATOR_H

#include <veamy/postprocess/NormCalculator.h>
#include <veamy/postprocess/analytic/StrainValue.h>
#include <veamy/postprocess/analytic/StressValue.h>
#include <feamy/postprocess/integrator/FeamyIntegrator.h>
#include <veamy/postprocess/computables/StrainStressDifferenceComputable.h>
#include <veamy/postprocess/computables/StrainStressComputable.h>
#include <veamy/postprocess/analytic/DisplacementValue.h>

/*
 * Computes the H1 norm
 */
template <typename T>
class H1NormCalculator : public NormCalculator<T> {
private:
    /*
     * Analytical stress, strain and displacement values
     */
    StressValue* stressValue;
    StrainValue* strainValue;
    DisplacementValue* value;
public:
    /*
     * Constructor
     */
    H1NormCalculator(StrainValue *strain, StressValue *stress, DisplacementValue* value, Eigen::VectorXd u, DOFS d,
                         std::vector<Point> points);

    /* Sets the calculators for this norm
     * @param integrator Calculator to use
     * @param info additional required information
     */
    void setCalculator(FeamyIntegrator<T>* integrator, FeamyAdditionalInfo info);

    /* Sets the calculators for this norm
     * @param integrator Calculator to use
     */
    void setCalculator(VeamyIntegrator<T>* integrator);
};

#endif