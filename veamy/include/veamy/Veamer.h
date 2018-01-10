#ifndef VEAMY_VEAMER_H
#define VEAMY_VEAMER_H

#include <delynoi/models/Mesh.h>
#include <veamy/models/dof/DOFS.h>
#include <veamy/models/constraints/EssentialConstraints.h>
#include <veamy/models/elements/VeamyElement.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/physics/conditions/Conditions.h>
#include <iostream>
#include "Calculator2D.h"
#include <utilities/utilities.h>
#include <veamy/postprocess/NormCalculator.h>

/*
 * Structure that returns the hash value of a polygon
 */
struct PolygonHasher {
    std::size_t operator()(const Polygon &k) const {
        using std::size_t;
        using std::hash;

        return k.hash;
    }
};


/*
 * Class that calculates the solution of the linear elasticity problem using the Virtual Element Method
 */
class Veamer : public Calculator2D<Polygon> {
protected:
    /*
     * Problem to solve
     */
    ProblemDiscretization<Polygon,Veamer>* problem;
public:
    /*
     * Constructor
     */
    Veamer(ProblemDiscretization<Polygon,Veamer>* problem);

    /*
     * Initializes the Veamer instance from the information in a text file
     * @param fileName name of the file to be read
     * @param material material to assign to the domain
     * @param force body force imposed on the system
     * @return mesh read from the file (geometric conditions)
     */
    Mesh<Polygon> initProblemFromFile(std::string fileName);

    /* Initializes the Veamer instance
     * @param m geometric conditions of the problem
     * @param conditions physical conditions of the problem
     */
    void initProblem(const Mesh<Polygon> &m);

    /* Computes an error norm
     * @param calculator class in charge of computing a norm
     * @param mesh mesh associated to the problem
     * @return error norm
     */
    NormResult computeErrorNorm(NormCalculator<Polygon>* calculator, Mesh<Polygon> mesh);
};


#endif
