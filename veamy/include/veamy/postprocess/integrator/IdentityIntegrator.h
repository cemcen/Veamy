#ifndef VEAMY_IDENTITYINTEGRATOR_H
#define VEAMY_IDENTITYINTEGRATOR_H

#include "NormIntegrator.h"
#include <delynoi/models/polygon/Polygon.h>

template <typename T>
class IdentityIntegrator : public NormIntegrator<T>{
public:
    double getIntegral(T poly, std::vector<Point> points);
    void setComputable(Computable<T>* c);
    NormIntegrator<T>* clone();
};

#endif