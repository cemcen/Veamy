#ifndef VEAMY_CALCULATORCONSTRUCTOR_H
#define VEAMY_CALCULATORCONSTRUCTOR_H

#include <veamy/postprocess/calculators/DisplacementCalculator.h>
#include <veamy/postprocess/calculators/StrainCalculator.h>
#include <veamy/models/dof/DOFS.h>
#include <veamy/lib/Eigen/Dense>

/*
 * Abstract class that encapsulates the construction of the strain and displacement calculators for different problems
 * solved using VEM
 */
template <typename T>
class CalculatorConstructor {
protected:
    /*
     * Degrees of freedom of the system
     */
    DOFS dofs;

    /*
     * Nodal values
     */
    Eigen::VectorXd u;
public:
    /*
     * Constructor
     */
    CalculatorConstructor(DOFS d, Eigen::VectorXd u){
        this->dofs = d;
        this->u = u;
    };

    /* Gets the corresponding DisplacementCalculator according to the problem solved
     * @param points mesh points
     * @return DisplacementCalculator instance
     */
    virtual DisplacementCalculator<T>* getDisplacementCalculator(std::vector<Point>& points) = 0;

    /* Gets the corresponding StrainCalculator according to the problem solved
     * @param points mesh points
     * @return StrainCalculator instance
     */
    virtual StrainCalculator<T>* getStrainCalculator(std::vector<Point> &points) = 0;
};

#endif