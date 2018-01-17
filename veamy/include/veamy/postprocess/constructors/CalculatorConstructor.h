#ifndef VEAMY_CALCULATORCONSTRUCTOR_H
#define VEAMY_CALCULATORCONSTRUCTOR_H

#include <veamy/postprocess/calculators/DisplacementCalculator.h>
#include <veamy/postprocess/calculators/StrainCalculator.h>
#include <veamy/models/dof/DOFS.h>
#include <veamy/lib/Eigen/Dense>

template <typename T>
class CalculatorConstructor {
protected:
    DOFS dofs;
    Eigen::VectorXd u;
public:
    CalculatorConstructor(DOFS d, Eigen::VectorXd u){
        this->dofs = d;
        this->u = u;
    };

    virtual DisplacementCalculator<T>* getDisplacementCalculator(std::vector<Point>& points) = 0;
    virtual StrainCalculator<T>* getStrainCalculator(   std::vector<Point> &points) = 0;
};

#endif