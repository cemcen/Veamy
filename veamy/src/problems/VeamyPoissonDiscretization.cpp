#include <veamy/problems/VeamyPoissonDiscretization.h>
#include <veamy/models/elements/PoissonVeamyElement.h>
#include <veamy/postprocess/calculators/VeamyPoissonDisplacementCalculator.h>
#include <veamy/postprocess/constructors/PoissonConstructor.h>

VeamyPoissonDiscretization::VeamyPoissonDiscretization(PoissonConditions *conditions) : ProblemDiscretization(conditions){
    this->conditions = conditions;
    this->numberDOF = 1;
}

Element<Polygon> *VeamyPoissonDiscretization::createElement(Veamer *v, Polygon &poly, UniqueList<Point> &points) {
    return new PoissonVeamyElement(this->conditions, poly, points, v->DOFs, this->numberDOF);
}

Mesh<Polygon> VeamyPoissonDiscretization::initProblemFromFile(std::string fileName) {
    //TODO: To be implemented
    return Mesh<Polygon>();
}

NormResult
VeamyPoissonDiscretization::computeErrorNorm(NormCalculator<Polygon> *calculator, Mesh<Polygon> mesh, Veamer *solver) {
    CalculatorConstructor<Polygon>* constructor = new PoissonConstructor<Polygon>(solver->DOFs, calculator->getNodalDisplacements());
    calculator->setCalculator(new VeamyIntegrator<Polygon>, constructor, mesh.getPoints().getList());

    calculator->setExtraInformation(this->conditions);

    return calculator->getNorm(mesh);
}
