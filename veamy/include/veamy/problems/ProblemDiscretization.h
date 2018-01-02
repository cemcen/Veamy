#ifndef VEAMY_PROBLEMDISCRETIZATION_H
#define VEAMY_PROBLEMDISCRETIZATION_H

#include <veamy/physics/conditions/Conditions.h>
#include <veamy/models/Element.h>

template <typename T, typename N>
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

    virtual Element<T>* createElement(N *solver, T &poly, UniqueList<Point> &points) = 0;
    virtual Mesh<T> initProblemFromFile(N *v, std::string fileName) = 0;
};
#endif