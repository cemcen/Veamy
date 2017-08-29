#ifndef VEAMY_MATERIALPLANESTRESS_H
#define VEAMY_MATERIALPLANESTRESS_H

#include "Material.h"

class MaterialPlaneStress: public Material{
public:
    MaterialPlaneStress(Materials::material m);
    MaterialPlaneStress(double young, double poisson);

    Eigen::MatrixXd getMaterialMatrix();
    double trace();
};

#endif
