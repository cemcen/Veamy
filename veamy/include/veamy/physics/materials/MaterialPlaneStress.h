#ifndef VEAMY_MATERIALPLANESTRESS_H
#define VEAMY_MATERIALPLANESTRESS_H

#include "Material.h"

/*
 * Models the material properties for plane stress conditions
 */
class MaterialPlaneStress: public Material{
public:
    /*
     * Constructor. Creates a material from the list of predefined materials included in Veamy
     */
    MaterialPlaneStress(Materials::material m);

    /*
     * Constructor. Creates a material given its properties
     */
    MaterialPlaneStress(double young, double poisson);

    /*
    * @return the material matrix (also called stress/strain tensor) for plane stress
    */
    Eigen::MatrixXd getMaterialMatrix();

    /*
     * @return trace of the material matrix
     */
    double trace();
};

#endif
