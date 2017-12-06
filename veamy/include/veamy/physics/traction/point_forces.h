#ifndef VEAMY_POINTFORCES_H
#define VEAMY_POINTFORCES_H

#include <veamy/models/constraints/NaturalConstraints.h>

namespace point_forces{
    extern void addPointForces(Eigen::VectorXd& tractionVector, NaturalConstraints natural, Point p1, Point p2);
}

#endif