#ifndef VEAMY_POISSONCONSTRUCTOR_H
#define VEAMY_POISSONCONSTRUCTOR_H

#include "CalculatorConstructor.h"

/*
 * Class that encapsulates the constructor of the calculators for the poisson problem
 */
template <typename T>
class PoissonConstructor : public CalculatorConstructor<T>{
public:
    /*
     * Constructor
     */
    PoissonConstructor(DOFS &d, const Eigen::VectorXd &u);

    /* Gets the corresponding DisplacementCalculator to poisson
     * @param points mesh points
     * @return VeamyPoissonDisplacementCalculator instance
     */
    DisplacementCalculator<T>* getDisplacementCalculator(std::vector<Point>& points);

    /* Gets the corresponding StrainCalculator to poisson
     * @param points mesh points
     * @return VeamyPoissonStrainCalculator instance
     */
    StrainCalculator<T>* getStrainCalculator(std::vector<Point> &points);
};

#endif