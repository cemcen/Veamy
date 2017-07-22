#ifndef MESHER_POINTGENERATOR_H
#define MESHER_POINTGENERATOR_H

#include <mesher/models/basic/Point.h>
#include <mesher/models/polygon/BoundingBox.h>
#include "Functor.h"
#include <vector>

class PointGenerator {
private:
    Functor* lX;
    Functor* lY;
public:
    PointGenerator(Functor* lX, Functor* lY);
    void generate(std::vector<Point>& vector, BoundingBox box, int nX, int nY);
};

#endif
