#ifndef VEAMY_FEAMER_H
#define VEAMY_FEAMER_H

#include <veamy/Calculator2D.h>
#include <veamy/physics/bodyforces/BodyForce.h>
#include <delynoi/models/polygon/Triangle.h>
#include <veamy/lib/Eigen/Dense>
#include <feamy/models/FeamyElement.h>
#include <feamy/models/constructor/FeamyElementConstructor.h>
#include <veamy/postprocess/NormCalculator.h>
#include <veamy/problems/ProblemDiscretization.h>

/*
 * Class that calculates the solution of the linear elasticity problem using the Finite Element Method
 */
class Feamer : public Calculator2D<Triangle>{
private:
    /*
    * Problem to solve
    */
    ProblemDiscretization<Triangle,Feamer>* problem;
public:
    /*
     * Constructor
     */
    Feamer(ProblemDiscretization<Triangle,Feamer>* problem);

    /* Initializes the Feamer instance
     * @param m geometric conditions of the problem
     * @param conditions physical conditions of the problem
     * @param constructor constructor used to create a certain type of FEM elements
     */
    void initProblem(Mesh<Triangle> m, FeamyElementConstructor *constructor);

    /* Computes an error norm
     * @param calculator class in charge of computing a norm
     * @param mesh mesh associated to the problem
     * @return error norm
     */
    NormResult computeErrorNorm(NormCalculator<Triangle>* calculator, Mesh<Triangle> mesh);

    /*
     * @return elements of the system
     */
    std::vector<FeamyElement*> getElements();
};

#endif