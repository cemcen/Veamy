#ifndef VEAMY_H1COMPUTABLE_H
#define VEAMY_H1COMPUTABLE_H

#include <veamy/postprocess/calculators/StrainCalculator.h>
#include <veamy/postprocess/computables/Computable.h>

/*
 * Represents a computable used strictly for the H1 norm computation.
 */
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
    /* Sets the value of the material matrix for stress computation from strain
     * @param D material matrix
     */
    void setMaterialMatrix(Eigen::MatrixXd D){
        this->D = D;
    };

    /* Sets the approximated strain calculator for the computable
     * @param calculator StrainCalculator instance to set
     */
    void setCalculator(StrainCalculator<T>* calculator){
        this->calculator = calculator;
    };
};

#endif