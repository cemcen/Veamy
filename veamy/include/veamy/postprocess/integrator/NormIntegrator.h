#ifndef VEAMY_NORMINTEGRATOR_H
#define VEAMY_NORMINTEGRATOR_H

#include <vector>
#include <delynoi/models/basic/Point.h>
#include <veamy/postprocess/computables/Computable.h>

/*
 * Abstract class that models the process of computing the integral in each norm
 */
template <class T>
class NormIntegrator {
protected:
    /*
     * Computable that will be integrated
     */
    Computable<T> *computable;
public:
    /* Computes the numerical integral value depending on the integration scheme implemented
     * @param poly polygon inside which the integral must be computed
     * @param polyIndex index of poly
     * @param points mesh points
     * @return the value of the integral
     */
    virtual double getIntegral(T poly, int polyIndex, std::vector<Point>& points) = 0;

    /* Sets a new Computable to integrate
     * @param c computable to integrate
     */
    virtual void setComputable(Computable<T>* c) = 0;

    /* Clones the instance, creating an identical copy in other memory space
     * @return pointer to a new NormIntegrator instance
     */
    virtual NormIntegrator* clone() = 0;
};

#endif