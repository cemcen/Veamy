#ifndef VEAMY_FEAMERINTEGRATOR_H
#define VEAMY_FEAMERINTEGRATOR_H

#include <delynoi/models/polygon/Triangle.h>
#include <veamy/postprocess/computables/Computable.h>
#include <veamy/postprocess/integrator/NormIntegrator.h>
#include <feamy/config/FeamyConfig.h>
#include <veamy/geometry/VeamyTriangle.h>
#include <veamy/postprocess/L2NormCalculator.h>

template <typename T>
class FeamyIntegrator : public  NormIntegrator<Triangle>{
private:
    Computable* computable;
public:
    FeamyIntegrator();
    FeamyIntegrator(Computable* computable);
    virtual double getIntegral(Triangle poly, std::vector<Point> points);
    void setComputable(Computable* c);
};

#endif