#ifndef VEAMY_IDENTITYINTEGRATOR_H
#define VEAMY_IDENTITYINTEGRATOR_H

#include "NormIntegrator.h"
#include <delynoi/models/polygon/Polygon.h>

/*
 * Class that does not actually integrate, but rather always returns 1 (used for cases when the norm is not computed
 * as a fraction for example)
 */
template <typename T>
class IdentityIntegrator : public NormIntegrator<T>{
public:
    double getIntegral(T poly, int polyIndex, std::vector<Point> points);

    /* Sets a new Computable to integrate
    * @param c computable to integrate
    */
    void setComputable(Computable<T>* c);

    /* Clones the instance, creating an identical copy in other memory space
     * @return pointer to a new IdentityIntegrator instance
     */
    NormIntegrator<T>* clone();
};

#endif