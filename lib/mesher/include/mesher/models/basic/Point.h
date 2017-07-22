#ifndef MESHER_POINT_H
#define MESHER_POINT_H

#include <string>
#include <math.h>
#include <cmath>
#include <sstream>
#include <utilities/utilities.h>

class Point {
private:
    double x;
    double y;
    bool isBoundaryPoint = false;
public:
    Point(double x, double y);
    Point();

    double getX() const;
    double getY() const;

    double squareNorm();
    std::string getString() const;
    bool operator==(const Point& other) const;
    bool operator<(const Point& other) const;
    Point operator-(const Point& other);
    double distance(Point p);

    bool isInBoundary();
    void setBoundary();

    void setX(double newX);
    void setY(double newY);

    void deform(double dX, double dY);
};

#endif