#ifndef VEAMY_INTEGRABLEFUNCTIONCOMPUTABLE_H
#define VEAMY_INTEGRABLEFUNCTIONCOMPUTABLE_H

#include <feamy/integration/integrables/IntegrableFunction.h>
#include "Computable.h"

/*
 * Class that wraps over a computable so that it can be integrated using a gaussian scheme as the rest of the
 * integrable functions
 */
template <typename T>
class IntegrableFunctionComputable: public IntegrableFunction<double>{
private:
    /*
     * Computable to integrate
     */
    Computable<T>* computable;
public:
    /*
     * Constructor
     */
    IntegrableFunctionComputable(Computable<T>* c){
        this->computable = c;
    }

    /* Method used to completely implement the IntegrableFunction interface, not actually used.
     */
    double apply(Point p){
        return 0;
    }

    /* Computes the value of the computable class in a given point inside a triangle
     * @param p point to apply the function
     * @param t container of the point
     * @return the value of the function
     */
    double apply(Point p,  VeamyTriangle t){
        return this->computable->apply(p.getX(), p.getY(), 0, t);
    }
};

#endif