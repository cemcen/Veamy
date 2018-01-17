#ifndef VEAMY_ELASTICITYCONSTRUCTOR_H
#define VEAMY_ELASTICITYCONSTRUCTOR_H

#include "CalculatorConstructor.h"

template <typename T>
class ElasticityConstructor : public CalculatorConstructor<T>{
public:
    ElasticityConstructor(DOFS d, Eigen::VectorXd u);

    DisplacementCalculator<T>* getDisplacementCalculator(std::vector<Point>& points);
    StrainCalculator<T>* getStrainCalculator(std::vector<Point> &points);
};

#endif