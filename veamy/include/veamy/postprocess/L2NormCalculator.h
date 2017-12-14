#ifndef VEAMY_L2NORMCALCULATOR_H
#define VEAMY_L2NORMCALCULATOR_H

#include <veamy/postprocess/NormCalculator.h>
#include <veamy/postprocess/analytic/DisplacementValue.h>
#include <feamy/postprocess/integrator/FeamyIntegrator.h>
#include <veamy/postprocess/integrator/VeamyIntegrator.h>
#include <feamy/postprocess/structures/FeamyAdditionalInfo.h>
#include <veamy/postprocess/computables/DisplacementDifferenceComputable.h>
#include <veamy/postprocess/computables/DisplacementComputable.h>
#include <veamy/postprocess/calculators/VeamyDisplacementCalculator.h>

/*
 * Computes the L2 norm
 */
template <typename T>
class L2NormCalculator: public NormCalculator<T> {
private:
    /*
     * Analytical displacement value
     */
    DisplacementValue* value;
public:
    /*
     * Constructor
     */
    L2NormCalculator(DisplacementValue* value, Eigen::VectorXd u, DOFS d);

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