#ifndef VEAMY_VEAMYH1INTEGRATOR_H
#define VEAMY_VEAMYH1INTEGRATOR_H

#include <delynoi/models/polygon/Polygon.h>
#include <veamy/postprocess/analytic/DisplacementValue.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/dof/DOFS.h>
#include "NormIntegrator.h"

/*
 * Class that computes the value of the approximation of the H1 norm for VEM
 */
template <typename T>
class VeamyH1Integrator : public NormIntegrator<T>{
private:
    /*
     * Analytical displacement value
     */
    DisplacementValue* value;

    /*
     * Degrees of freedom of the system
     */
    DOFS dofs;

    /*
     * Nodal displacement values
     */
    Eigen::VectorXd nodalValues;
public:
    /*
     * Default constructor
     */
    VeamyH1Integrator();

    /*
     * Constructor
     */
    VeamyH1Integrator(DisplacementValue* value, DOFS dofs, Eigen::VectorXd u);

    /* Computes the numerical integral value using the VEM approximation of the H1 norm
   * @param poly polygon inside which the integral must be computed
   * @param polyIndex index of poly
   * @param points mesh points
   * @return the value of the integral
   */
    double getIntegral(T poly, int polyIndex, std::vector<Point> points);

    /* Sets a new Computable to integrate
    * @param c computable to integrate
    */
    void setComputable(Computable<T>* c);

    /* Clones the instance, creating an identical copy in other memory space
     * @return pointer to a new VeamyH1Integrator instance
     */
    NormIntegrator<T>* clone();
};

#endif