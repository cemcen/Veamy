#ifndef VEAMY_INTEGRABLEFUNCTION_H
#define VEAMY_INTEGRABLEFUNCTION_H

#include <delynoi/models/basic/Point.h>

class IntegrableFunction{
public:
    virtual Eigen::VectorXd apply(Point p)=0;
};

#endif