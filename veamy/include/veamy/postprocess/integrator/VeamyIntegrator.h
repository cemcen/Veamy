#ifndef VEAMY_VEAMERCALCULATOR_H
#define VEAMY_VEAMERCALCULATOR_H

#include <veamy/postprocess/computables/Computable.h>
#include <delynoi/models/polygon/Polygon.h>
#include "NormIntegrator.h"

class VeamyIntegrator : public NormIntegrator<Polygon> {
private:
    Computable* computable;
public:
    VeamyIntegrator();
    VeamyIntegrator(Computable* computable);
    virtual double getIntegral(Polygon poly, std::vector<Point> points);
    void setComputable(Computable* c);
    NormIntegrator* clone();
};

#endif