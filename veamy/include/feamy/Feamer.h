#ifndef VEAMY_FEAMER_H
#define VEAMY_FEAMER_H

#include <veamy/Calculator2D.h>
#include <veamy/physics/bodyforces/BodyForce.h>
#include <delynoi/models/polygon/Triangle.h>
#include <veamy/lib/Eigen/Dense>
#include <feamy/models/FeamyElement.h>
#include <feamy/models/constructor/FeamyElementConstructor.h>
#include <veamy/postprocess/NormCalculator.h>

/*
 * Class that calculates the solution of the linear elasticity problem using the Finite Element Method
 */
class Feamer : public Calculator2D<Triangle>{
private:
    /*
     * Elements of the system
     */
    std::vector<FeamyElement*> elements;
public:
    /*
     * Default constructor
     */
    Feamer();

    /* Initializes the Feamer instance
     * @param m geometric conditions of the problem
     * @param conditions physical conditions of the problem
     * @param constructor constructor used to create a certain type of FEM elements
     */
    void initProblem(Mesh<Triangle> m, Conditions conditions, FeamyElementConstructor* constructor);

    /* Assembles the global stiffness matrix and load vector
     * @param KGlobal global stiffness matrix
     * @param fGlobal global load vector
     */
    void assemble(Eigen::MatrixXd& KGlobal, Eigen::VectorXd& fGlobal);

    /* Computes an error norm
     * @param calculator class in charge of computing a norm
     * @param mesh mesh associated to the problem
     * @return error norm
     */
    double computeErrorNorm(NormCalculator<Triangle>* calculator, Mesh<Triangle> mesh);
};

#endif