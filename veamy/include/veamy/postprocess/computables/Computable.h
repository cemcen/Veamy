#ifndef VEAMY_COMPUTABLE_H
#define VEAMY_COMPUTABLE_H

template <typename T>
class Computable {
public:
    virtual double apply(double x, double y, int index, T container) = 0;
    virtual void setPolygonIndex(int polyIndex){}
};

#endif