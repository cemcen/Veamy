#ifndef VEAMY_NORMCALCULATOR_H
#define VEAMY_NORMCALCULATOR_H

#include <delynoi/models/Mesh.h>
#include <veamy/postprocess/integrator/NormIntegrator.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/dof/DOFS.h>
#include <veamy/postprocess/integrator/VeamyIntegrator.h>
#include <feamy/postprocess/integrator/FeamyIntegrator.h>
#include <feamy/postprocess/structures/FeamyAdditionalInfo.h>

template <typename T>
class NormCalculator {
protected:
    NormIntegrator<T>* num;
    NormIntegrator<T>* den;

    Eigen::VectorXd nodalDisplacements;
    DOFS dofs;
public:
    NormCalculator(Eigen::VectorXd disp, DOFS dofs);
    double getNorm(Mesh<T> mesh);
    virtual void setCalculator(VeamyIntegrator<T>* integrator) = 0;
    virtual void setCalculator(FeamyIntegrator<T>* integrator, FeamyAdditionalInfo info) = 0;
};

#endif