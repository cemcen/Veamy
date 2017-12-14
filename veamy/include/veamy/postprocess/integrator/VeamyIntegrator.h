#ifndef VEAMY_VEAMERCALCULATOR_H
#define VEAMY_VEAMERCALCULATOR_H

#include <veamy/postprocess/computables/Computable.h>
#include <delynoi/models/polygon/Polygon.h>
#include "NormIntegrator.h"

/*
 * Class that integrates a given computable using the nodal integration scheme commonly used in VEM
 */
template <typename T>
class VeamyIntegrator : public NormIntegrator<T> {
public:
    /*
     * Default constructor
     */
    VeamyIntegrator();

    /*
     * Constructor
     */
    VeamyIntegrator(Computable<T>* computable);

    /* Computes the numerical integral value using a nodal integration scheme
   * @param poly polygon inside which the integral must be computed
   * @param polyIndex index of poly
   * @param points mesh points
   * @return the value of the integral
   */
    virtual double getIntegral(T poly, int polyIndex, std::vector<Point> points);

    /* Sets a new Computable to integrate
    * @param c computable to integrate
    */
    void setComputable(Computable<T>* c);

    /* Clones the instance, creating an identical copy in other memory space
     * @return pointer to a new VeamyIntegrator instance
     */
    NormIntegrator<T>* clone();
};

#endif