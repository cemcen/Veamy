#ifndef VEAMY_FEAMERINTEGRATOR_H
#define VEAMY_FEAMERINTEGRATOR_H

#include <delynoi/models/polygon/Triangle.h>
#include <veamy/postprocess/computables/Computable.h>
#include <veamy/postprocess/integrator/NormIntegrator.h>
#include <feamy/config/FeamyConfig.h>
#include <veamy/geometry/VeamyTriangle.h>

/*
 * Class that integrates a given computable using a gaussian quadrature scheme
 */
template <typename T>
class FeamyIntegrator : public NormIntegrator<T>{
public:
    /*
     * Default constructor
     */
    FeamyIntegrator();

    /*
     * Constructor
     */
    FeamyIntegrator(Computable<T>* computable);

    /* Computes the numerical integral value using a gaussian quadrature scheme
  * @param poly element inside which the integral must be computed
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
     * @return pointer to a new FeamyIntegrator instance
     */
    NormIntegrator<T>* clone();
};

#endif