#ifndef VEAMY_MATERIALPLAINSTRESS_H
#define VEAMY_MATERIALPLAINSTRESS_H

#include "Material.h"

class MaterialPlaneStress: public Material{
public:
    MaterialPlaneStress(Materials::material m);
    MaterialPlaneStress(double young, double poisson);

    Eigen::MatrixXd getMaterialMatrix();
    double trace();
};

#endif