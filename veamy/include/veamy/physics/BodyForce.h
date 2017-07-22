#ifndef VEAMY_BODYFORCE_H
#define VEAMY_BODYFORCE_H

class BodyForce{
public:
    virtual double applyX(double x, double y) = 0;
    virtual double applyY(double x, double y) = 0;

    virtual Pair<double> computeVector(Polygon p, std::vector<Point> points) = 0;
};

#endif