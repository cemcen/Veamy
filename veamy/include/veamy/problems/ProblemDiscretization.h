#ifndef VEAMY_PROBLEMDISCRETIZATION_H
#define VEAMY_PROBLEMDISCRETIZATION_H

#include <veamy/physics/conditions/Conditions.h>
#include <veamy/models/Element.h>
#include <veamy/postprocess/NormCalculator.h>
#include <veamy/postprocess/utilities/NormResult.h>

/*
 * Abstract class that models a problem to be solved by any method
 */
template <typename T, typename N>
class ProblemDiscretization{
protected:
    /*
     * Number of degrees of freedom per point
     */
    int numberDOF;

    /*
     * Conditions of the problem
     */
    Conditions* conditions;
public:
    /*
     * Constructor
     */
    ProblemDiscretization(Conditions* conditions){
        this->conditions = conditions;
    }

    /*
     * @return number of degrees of freedom per point
     */
    int numberOfDOFs(){
        return numberDOF;
    }

    /*
     * @return conditions of the problem
     */
    Conditions* getConditions(){
        return conditions;
    }

    /* Creates an Element according to the problem and the solver
     * @param solver solver representing the method that will be used
     * @param poly geometric equivalent of the element
     * @param points mesh points
     * @return created element
     */
    virtual Element<T>* createElement(N *solver, T &poly, UniqueList<Point> &points) = 0;

    /* Creates a problem from a text file
     * @param fileName name of the text file
     */
    virtual Mesh<T> initProblemFromFile(std::string fileName) = 0;

    /* Computes an error norm
     * @param calculator class in charge of calculating the norm
     * @param mesh mesh in which the error will be computed
     * @param solver solver that solved the problem
     */
    virtual NormResult computeErrorNorm(NormCalculator<T> *calculator, Mesh<T>& mesh, N* solver) = 0;
};
#endif