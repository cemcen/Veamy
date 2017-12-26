#ifndef VEAMY_PROBLEMDISCRETIZATION_H
#define VEAMY_PROBLEMDISCRETIZATION_H

#include <veamy/physics/conditions/Conditions.h>

class ProblemDiscretization{
protected:
    int numberDOF;
    Conditions* conditions;
public:
    int numberOfDOFs(){
        return numberDOF;
    }

    virtual DOFS* createDOFS() = 0;
    virtual Element* createElement(Polygon* poly, const std::vector<Point>& points) = 0;

};
#endif