#ifndef VEAMY_CALCULATOR_H
#define VEAMY_CALCULATOR_H

#include <vector>
#include <delynoi/models/basic/Point.h>

template <class T>
class NormIntegrator{
public:
    virtual double getIntegral(T poly, std::vector<Point> points) = 0;
    virtual void setComputable(Computable* c) = 0;
    virtual NormIntegrator* clone() = 0;
};

#endif