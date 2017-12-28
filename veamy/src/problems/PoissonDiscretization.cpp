#include <veamy/problems/PoissonDiscretization.h>
#include <veamy/models/elements/PoissonVeamyElement.h>

PoissonDiscretization::PoissonDiscretization(PoissonConditions *conditions) : ProblemDiscretization(conditions){
    this->conditions = conditions;
    this->numberDOF = 1;
}

Element *PoissonDiscretization::createElement(Veamer *v, Polygon &poly, UniqueList<Point> &points) {
    return new PoissonVeamyElement(this->conditions, poly, points, v->DOFs, this->numberDOF);
}

Element *PoissonDiscretization::createElement(Feamer *f, Triangle &poly, UniqueList<Point> &points) {
    return nullptr;
}
