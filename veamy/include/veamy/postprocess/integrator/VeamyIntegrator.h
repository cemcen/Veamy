#ifndef VEAMY_VEAMERCALCULATOR_H
#define VEAMY_VEAMERCALCULATOR_H

#include <veamy/postprocess/computables/Computable.h>
#include <delynoi/models/polygon/Polygon.h>
#include "NormIntegrator.h"

template <typename T>
class VeamyIntegrator : public NormIntegrator<T> {
public:
    VeamyIntegrator();
    VeamyIntegrator(Computable<T>* computable);
    virtual double getIntegral(T poly, int polyIndex, std::vector<Point> points);
    void setComputable(Computable<T>* c);
    NormIntegrator<T>* clone();
};

#endif