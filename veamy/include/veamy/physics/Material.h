#ifndef THESIS_MATERIAL_H
#define THESIS_MATERIAL_H

#include <veamy/lib/Eigen/Dense>
#include <veamy/physics/materials/Materials.h>

class Material{
private:
    double material_E;
    double material_v;
public:
    Material(Materials::material m);
    Material(double young, double poisson);
    Material();

    Eigen::MatrixXd getMaterialMatrix();
    Eigen::MatrixXd getPlaneStressMatrix();
    double trace();
    double tracePlaneStress();

    double k();
    double v();
    double E();
    bool operator==(const Material& other) const;
};

#endif
