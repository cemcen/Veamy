#ifndef VEAMY_POISSONCONSTRUCTOR_H
#define VEAMY_POISSONCONSTRUCTOR_H

#include "CalculatorConstructor.h"

template <typename T>
class PoissonConstructor : public CalculatorConstructor<T>{
public:
    PoissonConstructor(DOFS d, Eigen::VectorXd u);

    DisplacementCalculator<T>* getDisplacementCalculator(std::vector<Point>& points);
    StrainCalculator<T>* getStrainCalculator(std::vector<Point> &points);
};

#endif