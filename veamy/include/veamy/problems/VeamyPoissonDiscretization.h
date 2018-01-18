#ifndef VEAMY_POISSONDISCRETIZATION_H
#define VEAMY_POISSONDISCRETIZATION_H

#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/physics/conditions/PoissonConditions.h>
#include <veamy/Veamer.h>
#include "ProblemDiscretization.h"

/*
 * Class that models the resolution of the Poisson problem using the Virtual Element Method
 */
class VeamyPoissonDiscretization : public ProblemDiscretization<Polygon,Veamer>{
public:
    /*
     * Conditions of the poisson problem
     */
    PoissonConditions* conditions;

    /*
     * Constructor
     */
    VeamyPoissonDiscretization(PoissonConditions* conditions);

    /* Creates a VeamyPoissonElement
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
    Mesh<Polygon> initProblemFromFile(std::string fileName);

    /* Computes an error norm
     * @param calculator class in charge of calculating the norm
     * @param mesh mesh in which the error will be computed
     * @param solver solver that solved the problem
     */
    NormResult computeErrorNorm(NormCalculator<Polygon> *calculator, Mesh<Polygon> mesh, Veamer* solver);
};

#endif