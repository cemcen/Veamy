#ifndef VEAMY_LINEARELASTICITYDISCRETIZATION_H
#define VEAMY_LINEARELASTICITYDISCRETIZATION_H

#include <veamy/physics/conditions/LinearElasticityConditions.h>
#include <veamy/models/Element.h>
#include <veamy/Veamer.h>
#include <veamy/postprocess/utilities/NormResult.h>
#include "ProblemDiscretization.h"

/*
 * Class that represents the resolution of the linear elasticity problem using the Virtual Element Method
 */
class VeamyLinearElasticityDiscretization : public ProblemDiscretization<Polygon,Veamer>{
public:
    /*
     * Conditions of the linear elasticity problem
     */
    LinearElasticityConditions* conditions;

    /*
     * Constructor
     */
    VeamyLinearElasticityDiscretization(LinearElasticityConditions* conditions);

    /* Creates a VeamyElasticityElement
     * @param solver solver representing the method that will be used
     * @param poly geometric equivalent of the element
     * @param points mesh points
     * @return created element
     */
    Element<Polygon>* createElement(Veamer *v, Polygon &poly, UniqueList<Point> &points);

    /* Creates a problem from a text file
     * @param solver solver representing the method that will be used
     * @param fileName name of the text file
     */
    Mesh<Polygon> initProblemFromFile(Veamer *v, std::string fileName);

    /* Computes an error norm
    * @param calculator class in charge of calculating the norm
    * @param mesh mesh in which the error will be computed
    * @param solver solver that solved the problem
    */
    NormResult computeErrorNorm(NormCalculator<Polygon> *calculator, Mesh<Polygon> mesh, Veamer* veamer);
};

#endif