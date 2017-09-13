#ifndef VEAMY_BOUNDARYVECTORINTEGRABLE_H
#define VEAMY_BOUNDARYVECTORINTEGRABLE_H

#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <veamy/lib/Eigen/Dense>
#include "IntegrableFunction.h"

class BoundaryVectorIntegrable : public IntegrableFunction{
private:
    ShapeFunctions* N;
public:
    Eigen::VectorXd apply(Point p){

    }

};

#endif