#ifndef VEAMY_CALCULATOR_H
#define VEAMY_CALCULATOR_H

#include <vector>
#include <delynoi/models/basic/Point.h>
#include <veamy/postprocess/computables/Computable.h>

template <class T>
class NormIntegrator {
protected:
    Computable<T> *computable;
public:
    virtual double getIntegral(T poly, int polyIndex, std::vector<Point> points) = 0;
    virtual void setComputable(Computable<T>* c) = 0;
    virtual NormIntegrator* clone() = 0;
};

#endif