#ifndef VEAMY_BOUNDARYVECTORINTEGRABLE_H
#define VEAMY_BOUNDARYVECTORINTEGRABLE_H

#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/geometry/VeamyTriangle.h>
#include "IntegrableFunction.h"

class BoundaryVectorIntegrable : public IntegrableFunction{
private:
    ShapeFunctions* N;
    NaturalConstraints natural;
    VeamyTriangle triangle;
public:
    Eigen::VectorXd apply(Point p){


    }

};

#endif