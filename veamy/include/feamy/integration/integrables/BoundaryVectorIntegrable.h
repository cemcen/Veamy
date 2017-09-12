#ifndef VEAMY_BOUNDARYVECTORINTEGRABLE_H
#define VEAMY_BOUNDARYVECTORINTEGRABLE_H

#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include "IntegrableFunction.h"

class BoundaryVectorIntegrable : public IntegrableFunction{
private:
    ShapeFunctions* N;

};

#endif