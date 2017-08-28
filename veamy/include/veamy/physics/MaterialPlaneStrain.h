#ifndef VEAMY_MATERIALPLANESTRAIN_H
#define VEAMY_MATERIALPLANESTRAIN_H

#include "Material.h"

class MaterialPlaneStrain: public Material{
public:
    MaterialPlaneStrain(Materials::material m);
    MaterialPlaneStrain(double young, double poisson);

    Eigen::MatrixXd getMaterialMatrix();
    double trace();
};

#endif