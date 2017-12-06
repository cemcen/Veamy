#ifndef VEAMY_INTEGRABLEFUNCTIONCOMPUTABLE_H
#define VEAMY_INTEGRABLEFUNCTIONCOMPUTABLE_H

#include <feamy/integration/integrables/IntegrableFunction.h>
#include "Computable.h"

template <typename T>
class IntegrableFunctionComputable: public IntegrableFunction<double>{
private:
    Computable<T>* computable;
public:
    IntegrableFunctionComputable(Computable<T>* c){
        this->computable = c;
    }

    double apply(Point p){
        return 0;
    }

    double apply(Point p,  VeamyTriangle t){
        return this->computable->apply(p.getX(), p.getY(), 0, t);
    }
};

#endif