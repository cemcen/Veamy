#ifndef VEAMY_NORMCALCULATOR_H
#define VEAMY_NORMCALCULATOR_H

#include <delynoi/models/Mesh.h>
#include <veamy/Veamer.h>
#include <feamy/Feamer.h>
#include <veamy/postprocess/integrator/NormIntegrator.h>
#include <veamy/postprocess/values/methods.h>

template <typename T>
class NormCalculator {
protected:
    NormIntegrator* num;
    NormIntegrator* den;

    Eigen::VectorXd nodalDisplacements;
    DOFS dofs;
public:
    NormCalculator(Eigen::VectorXd disp, DOFS dofs);
    double getNorm(Mesh<T> mesh);
    virtual void setCalculators(NormIntegrator* num, NormIntegrator* den);
};

#endif