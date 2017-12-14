#ifndef VEAMY_MATERIALPLANESTRAIN_H
#define VEAMY_MATERIALPLANESTRAIN_H

#include "Material.h"

/*
 * Models the material properties for plane strain conditions
 */
class MaterialPlaneStrain: public Material{
public:
    /*
     * Constructor. Creates a material from the list of predefined materials included in Veamy
     */
    MaterialPlaneStrain(Materials::material m);

    /*
     * Constructor. Creates a material given its properties
     */
    MaterialPlaneStrain(double young, double poisson);

    /*
    * @return the material matrix (also called stress/strain tensor) for plane strain
    */
    Eigen::MatrixXd getMaterialMatrix();

    /*
     * @return trace of the material matrix
     */
    double trace();
};

#endif