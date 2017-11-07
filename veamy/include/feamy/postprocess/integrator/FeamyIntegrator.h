#ifndef VEAMY_FEAMERINTEGRATOR_H
#define VEAMY_FEAMERINTEGRATOR_H

#include <delynoi/models/polygon/Triangle.h>
#include <veamy/postprocess/computables/Computable.h>
#include <veamy/postprocess/integrator/NormIntegrator.h>
#include <feamy/config/FeamyConfig.h>
#include <veamy/geometry/VeamyTriangle.h>

template <typename T>
class FeamyIntegrator : public NormIntegrator<T>{
public:
    FeamyIntegrator();
    FeamyIntegrator(Computable<T>* computable);
    virtual double getIntegral(T poly, std::vector<Point> points);
    void setComputable(Computable<T>* c);
    NormIntegrator<T>* clone();
};

#endif