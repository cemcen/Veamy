#ifndef VEAMY_H1COMPUTABLE_H
#define VEAMY_H1COMPUTABLE_H

#include <veamy/postprocess/calculators/StrainCalculator.h>
#include <veamy/postprocess/computables/Computable.h>

template <typename T>
class H1Computable : public Computable<T>{
protected:
    /*
     * Material matrix
     */
    Eigen::MatrixXd D;

    /*
     * Class in charge of computing the approximated strain
     */
    StrainCalculator<T>* calculator;
public:
    void setMaterialMatrix(Eigen::MatrixXd D){
        this->D = D;
    };

    void setCalculator(StrainCalculator<T>* calculator){
        this->calculator = calculator;
    };
};

#endif