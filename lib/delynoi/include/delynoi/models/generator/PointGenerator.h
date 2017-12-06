#ifndef DELYNOI_POINTGENERATOR_H
#define DELYNOI_POINTGENERATOR_H

#include <delynoi/models/basic/Point.h>
#include <delynoi/models/polygon/BoundingBox.h>
#include "Functor.h"
#include "delynoi/models/generator/functions/functions.h"
#include <vector>

class PointGenerator {
private:
    Functor* lX;
    Functor* lY;
    functions::independent_variable variable;

    Point result(double x, double y);
public:
    PointGenerator();
    PointGenerator(Functor* lX, Functor* lY);
    PointGenerator(Functor* l, functions::independent_variable variable);
    virtual void generate(std::vector<Point>& vector, BoundingBox box, int nX, int nY);
};

#endif
