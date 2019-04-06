#ifndef VEAMY_ELASTICITYCONSTRUCTOR_H
#define VEAMY_ELASTICITYCONSTRUCTOR_H

#include "CalculatorConstructor.h"

/*
 * Class that encapsulates the constructor of the calculators for the elasticity problem
 */
template <typename T>
class ElasticityConstructor : public CalculatorConstructor<T>{
public:
    /*
     * Constructor
     */
    ElasticityConstructor(DOFS &d, const Eigen::VectorXd &u);

    /* Gets the corresponding DisplacementCalculator to elasticity
     * @param points mesh points
     * @return VeamyElasticityDisplacementCalculator instance
     */
    DisplacementCalculator<T>* getDisplacementCalculator(std::vector<Point>& points);

    /* Gets the corresponding StrainCalculator to elasticity
     * @param points mesh points
     * @return VeamyElasticityStrainCalculator instance
     */
    StrainCalculator<T>* getStrainCalculator(std::vector<Point> &points);
};

#endif