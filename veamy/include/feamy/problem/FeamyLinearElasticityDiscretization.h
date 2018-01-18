#ifndef VEAMY_FEAMYLINEARELASTICITYDISCRETIZATION_H
#define VEAMY_FEAMYLINEARELASTICITYDISCRETIZATION_H

#include <feamy/Feamer.h>
#include <delynoi/models/polygon/Triangle.h>
#include <veamy/physics/conditions/LinearElasticityConditions.h>

/*
 * Class that model the resolution of the linear elasticity
 */
class FeamyLinearElasticityDiscretization : public ProblemDiscretization<Triangle,Feamer>{
public:
    /*
     * Conditions of the linear elasticity problem
     */
    LinearElasticityConditions* conditions;

    /*
     * Constructor
     */
    FeamyLinearElasticityDiscretization(LinearElasticityConditions* conditions);

    /* Creates a FeamyPoissonElement
     * @param solver solver representing the method that will be used
     * @param poly geometric equivalent of the element
     * @param points mesh points
     * @return created element
     */
    Element<Triangle>* createElement(Feamer *f, Triangle &poly, UniqueList<Point> &points);

    /* Creates a problem from a text file
     * @param solver solver representing the method that will be used
     * @param fileName name of the text file
     */
    Mesh<Triangle> initProblemFromFile(std::string fileName);

    /* Computes an error norm
    * @param calculator class in charge of calculating the norm
    * @param mesh mesh in which the error will be computed
    * @param solver solver that solved the problem
    */
    NormResult computeErrorNorm(NormCalculator<Triangle> *calculator, Mesh<Triangle> mesh, Feamer* f);
};

#endif