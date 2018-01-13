#include <veamy/problems/VeamyPoissonDiscretization.h>
#include <veamy/models/elements/PoissonVeamyElement.h>

VeamyPoissonDiscretization::VeamyPoissonDiscretization(PoissonConditions *conditions) : ProblemDiscretization(conditions){
    this->conditions = conditions;
    this->numberDOF = 1;
}

Element<Polygon> *VeamyPoissonDiscretization::createElement(Veamer *v, Polygon &poly, UniqueList<Point> &points) {
    return new PoissonVeamyElement(this->conditions, poly, points, v->DOFs, this->numberDOF);
}

Mesh<Polygon> VeamyPoissonDiscretization::initProblemFromFile(Veamer *v, std::string fileName) {
    //TODO: To be implemented
    return Mesh<Polygon>();
}

NormResult
VeamyPoissonDiscretization::computeErrorNorm(NormCalculator<Polygon> *calculator, Mesh<Polygon> mesh, Veamer *solver) {
    //TODO: To be implemented
    return NormResult(0, 0);
}
