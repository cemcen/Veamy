#ifndef VEAMY_VEAMYH1INTEGRATOR_H
#define VEAMY_VEAMYH1INTEGRATOR_H

#include <delynoi/models/polygon/Polygon.h>
#include <veamy/postprocess/analytic/DisplacementValue.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/dof/DOFS.h>
#include "NormIntegrator.h"

template <typename T>
class VeamyH1Integrator : public NormIntegrator<T>{
private:
    DisplacementValue* value;
    DOFS dofs;
    Eigen::VectorXd nodalValues;
public:
    VeamyH1Integrator();
    VeamyH1Integrator(DisplacementValue* value, DOFS dofs, Eigen::VectorXd u);
    double getIntegral(T poly, std::vector<Point> points);
    void setComputable(Computable<T>* c);
    NormIntegrator<T>* clone();
};

#endif