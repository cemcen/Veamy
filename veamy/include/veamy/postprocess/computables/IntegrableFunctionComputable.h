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

    inline double apply(Point p){
        return this->computable->apply(p.getX(), p.getY(), 0, T());
    }
};

#endif