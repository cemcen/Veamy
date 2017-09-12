#ifndef DELYNOI_CIRCLE_H
#define DELYNOI_CIRCLE_H

#include <vector>
#include <delynoi/models/basic/Point.h>
#include <cstdlib>
#include <cmath>
#include <delynoi/utilities/geometryFunctions.h>
#include <delynoi/utilities/xpolyutilities.h>

class Circle {
protected:
    double radius;
    Point center;
public:
    Circle(double r, Point c);
    std::vector<Point> discretizeCircle();
};


#endif
