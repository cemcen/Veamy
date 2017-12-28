#ifndef VEAMY_PROBLEMDISCRETIZATION_H
#define VEAMY_PROBLEMDISCRETIZATION_H

#include <veamy/physics/conditions/Conditions.h>
#include <veamy/Veamer.h>
#include <feamy/Feamer.h>

class Veamer;

class ProblemDiscretization{
protected:
    int numberDOF;
    Conditions* conditions;
public:
    ProblemDiscretization(Conditions* conditions){
        this->conditions = conditions;
    }

    int numberOfDOFs(){
        return numberDOF;
    }

    Conditions* getConditions(){
        return conditions;
    }

    virtual Element* createElement(Veamer *veamer, Polygon &poly, UniqueList<Point> &points) = 0;
    virtual Element* createElement(Feamer *veamer, Triangle &poly, UniqueList<Point> &points) = 0;
    virtual Mesh<Polygon> initProblemFromFile(Veamer *v, std::string fileName) = 0;


};
#endif