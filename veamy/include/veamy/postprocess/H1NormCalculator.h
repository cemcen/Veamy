#ifndef VEAMY_H1NORMCALCULATOR_H
#define VEAMY_H1NORMCALCULATOR_H

#include <veamy/postprocess/NormCalculator.h>
#include <veamy/postprocess/analytic/StrainValue.h>
#include <veamy/postprocess/analytic/StressValue.h>
#include <feamy/postprocess/integrator/FeamyIntegrator.h>
#include <veamy/postprocess/computables/StrainStressDifferenceComputable.h>
#include <veamy/postprocess/computables/StrainStressComputable.h>
#include <veamy/postprocess/analytic/DisplacementValue.h>
#include <veamy/postprocess/integrator/IdentityIntegrator.h>
#include <veamy/postprocess/computables/StrainComputable.h>
#include <feamy/postprocess/calculators/FeamyStrainCalculator.h>
#include <veamy/physics/conditions/LinearElasticityConditions.h>
#include <veamy/postprocess/computables/StrainDifferenceComputable.h>
#include <veamy/postprocess/calculators/VeamyStrainCalculator.h>

/*
 * Computes the H1 norm
 */
template <typename T>
class H1NormCalculator : public NormCalculator<T> {
private:
    /*
     * Analytical stress and strain values
     */
    StressValue* stressValue;
    StrainValue* strainValue;

    /*
     * Material matrix
     */
    Eigen::MatrixXd D;

    /*
     * Computables corresponding to the numerator and denominator
     */
    H1Computable<T>* numComputable;
    H1Computable<T>* denComputable;
public:
    /*
     * Constructor
     */
    H1NormCalculator(StrainValue *strain, StressValue *stress, Eigen::VectorXd u, DOFS d);

    /*
    * Constructor
    */
    H1NormCalculator(StrainValue *strain, Eigen::VectorXd u, DOFS d);

    /* Sets the calculators for this norm
     * @param integrator Calculator to use
     * @param info additional required information
     */
    void setCalculator(FeamyIntegrator<T>* integrator, FeamyAdditionalInfo info);

    /* Sets the calculators for this norm
     * @param integrator Calculator to use
     */
    void setCalculator(VeamyIntegrator<T> *integrator, Calculator<T> *calculator);

    /* Sets all extra information from the problem conditions that is used for norm computation
     * @param conditions problem conditions
     */
    void setExtraInformation(Conditions* conditions);
};

#endif