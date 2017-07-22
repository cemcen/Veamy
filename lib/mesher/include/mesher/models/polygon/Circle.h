#ifndef MESHER_CIRCLE_H
#define MESHER_CIRCLE_H

#include <vector>
#include <mesher/models/basic/Point.h>
#include <cstdlib>
#include <cmath>
#include <mesher/utilities/geometryFunctions.h>
#include <mesher/utilities/xpolyutilities.h>

class Circle {
protected:
    double radius;
    Point center;
public:
    Circle(double r, Point c);
    std::vector<Point> discretizeCircle();
};


#endif
