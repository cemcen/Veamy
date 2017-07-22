#ifndef THESIS_BODYFORCEVECTOR_H
#define THESIS_BODYFORCEVECTOR_H

#include <mesher/models/polygon/Polygon.h>
#include <vector>
#include <veamy/physics/BodyForce.h>

class BodyForceVector {
private:
    Polygon polygon;
public:
    BodyForceVector(Polygon p);
    double computeVector(BodyForce *f, std::vector<Point> points);
};


#endif
