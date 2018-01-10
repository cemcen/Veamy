#ifndef VEAMY_NORMCALCULATOR_H
#define VEAMY_NORMCALCULATOR_H

#include <delynoi/models/Mesh.h>
#include <veamy/postprocess/integrator/NormIntegrator.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/dof/DOFS.h>
#include <veamy/postprocess/integrator/VeamyIntegrator.h>
#include <feamy/postprocess/integrator/FeamyIntegrator.h>
#include <feamy/postprocess/structures/FeamyAdditionalInfo.h>
#include <veamy/postprocess/utilities/NormResult.h>

/*
 * Abstract class that encapsulates the generic formula used to calculate the norms, leaving responsability to the
 * actual computation to concrete implementations
 */
template <typename T>
class NormCalculator {
protected:
    /*
     * Calculator of the numerator of the norm formula
     */
    NormIntegrator<T>* num;

    /*
    * Calculator of the denominator of the norm formula
    */
    NormIntegrator<T>* den;

    /*
     * Nodal displacement values
     */
    Eigen::VectorXd nodalDisplacements;

    /*
     * Degrees of freedom of the system
     */
    DOFS dofs;
public:
    NormCalculator(Eigen::VectorXd disp, DOFS dofs);

    /* Computes the norm
     * @param mesh mesh in which the norm will be computed
     * @return value of the norm
     */
    NormResult getNorm(Mesh<T> mesh);

    /* Sets the calculators for this norm
     * @param integrator Calculator to use
     */
    virtual void setCalculator(VeamyIntegrator<T> *integrator, std::vector<Point> &points) = 0;

    /* Sets the calculators for this norm
     * @param integrator Calculator to use
     * @param info additional required information
     */
    virtual void setCalculator(FeamyIntegrator<T>* integrator, FeamyAdditionalInfo info) = 0;

    /* Obtains any extra information required for the norm from the problem conditions
     * @param conditions problem conditions
     */
    virtual void setExtraInformation(Conditions* conditions) = 0;
};

#endif