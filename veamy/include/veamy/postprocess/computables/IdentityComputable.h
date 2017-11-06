#ifndef VEAMY_IDENTITYCOMPUTABLE_H
#define VEAMY_IDENTITYCOMPUTABLE_H

#include <delynoi/models/polygon/Polygon.h>
#include "Computable.h"

class IdentityComputable : public Computable<Polygon>{
public:
    double apply(double x, double y, int index, Polygon container);
};

#endif